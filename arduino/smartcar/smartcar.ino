#include <MQTT.h>
#include <WiFi.h>
#ifdef SMCE
#include <OV767X.h>
#endif
#include <Smartcar.h>
#include <cmath>

//--------------------VARIABLES DECLARATION----------------------------------//

MQTTClient mqtt;
WiFiClient net;

int        port     = 1883;
const char ssid[] = "***";
const char pass[] = "****";

ArduinoRuntime arduinoRuntime;
BrushedMotor leftMotor(arduinoRuntime, smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(arduinoRuntime, smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control(leftMotor, rightMotor);
const int GYROSCOPE_OFFSET = 37;
GY50 gyro(arduinoRuntime, GYROSCOPE_OFFSET);

SimpleCar car(control);

const int triggerPin           = 6;
const int echoPin              = 7;
const int BACK_PIN          = 3;
const auto mqttBrokerUrl = "broker.emqx.io";

const unsigned int maxDistance = 300;
const int fspeed = 50;
const int bspeed = -50;
int stopSpeed = 0;

SR04 front{arduinoRuntime, triggerPin, echoPin, maxDistance};
GP2Y0A21 back(arduinoRuntime, BACK_PIN);



//--------------------MQTT CONNECTIONS----------------------------------//

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, pass);
  mqtt.begin(mqttBrokerUrl, port, net);

  Serial.println("Connecting to WiFi...");
  auto wifiStatus = WiFi.status();
  Serial.println(wifiStatus);
  while (wifiStatus != WL_CONNECTED && wifiStatus != WL_NO_SHIELD) {
    Serial.println(wifiStatus);
    Serial.print(".");
    delay(1000);
    wifiStatus = WiFi.status();
  }

  Serial.println("Connecting to MQTT broker");
  while (!mqtt.connect("arduino", "public", "public")) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected successfully.");
  mqtt.subscribe("smartcar/control/#", 1);

  mqtt.onMessage([](String topic, String message) {
    static auto starttime = 0;
    static auto endtime = 0;

    Serial.println(topic + " " + message);
      if (topic ==  "smartcar/control/throttle") {
        Serial.println(topic);
        starttime = millis();
        endtime = starttime;
        while ((endtime - starttime) <= message.toInt() * 1000) {
          car.setSpeed(fspeed);
          car.setAngle(0);
          endtime = millis();
        }
        car.setSpeed(0);
        car.setAngle(0);
      }
      else if(topic == "smartcar/control/turn") {

      }
      else if(topic == "smartcar/control/spin") {

      }
      else if(topic == "smartcar/control/wait") {
        Serial.println(topic);
        starttime = millis();
        endtime = starttime;
        while ((endtime - starttime) <= message.toInt() * 1000) {
          car.setSpeed(0);
          car.setAngle(0);
          endtime = millis();
        }
      
      }


      else if (topic == "smartcar/control/reverse") {
        Serial.println(topic);
        starttime = millis();
        endtime = starttime;
        while ((endtime - starttime) <= message.toInt() * 1000) {
          car.setSpeed(bspeed);
          car.setAngle(0);
          endtime = millis();
        }
        car.setSpeed(0);
        car.setAngle(0);
      }

      if (topic == "smartcar/control/steer-left") {
        
        int angleValue = 0;
        double inputAngle = -message.toInt();

        car.setAngle(inputAngle);
        gyro.update();
        angleValue = gyro.getHeading();
        int finalDegree = (gyro.getHeading() + -inputAngle) > 360 ? (gyro.getHeading() + -inputAngle) -360 : (gyro.getHeading() + -inputAngle);

        while (angleValue != finalDegree){
          car.setSpeed(fspeed);
          Serial.println(angleValue);
          gyro.update();
          angleValue = gyro.getHeading();
        }

        stopCar();
        Serial.println(gyro.getHeading());
      }

      if (topic == "smartcar/control/steer-right") {
         
        int angleValue = 0;
        double inputAngle = message.toInt();

        car.setAngle(inputAngle);
        gyro.update();
        angleValue = gyro.getHeading();
        /*int finalDegree = (gyro.getHeading() + inputAngle) < 0 ? (360 + (gyro.getHeading() + inputAngle)) : (gyro.getHeading() + -inputAngle);
        */
        int finalDegree = gyro.getHeading() + -inputAngle;
        if (finalDegree < 0){
          finalDegree = 360 + finalDegree;
        }
        Serial.println(finalDegree);
        
        while (angleValue != finalDegree){
          car.setSpeed(fspeed);
          
          gyro.update();
          angleValue = gyro.getHeading();
        }

        stopCar();
        Serial.println(gyro.getHeading());
      }
      

      else {
        Serial.println(topic + " " + message);
      }
    }
  );   
}

void loop() {
  detectObstacle();
  if (mqtt.connected()) {
    mqtt.loop();
    //Probably need to change some stuff here
    #ifdef SMCE
      // Avoid over-using the CPU if we are running in the emulator
      delay(1);
    #endif
  } 
  else {
    mqtt.connect("arduino", "public", "public");
    mqtt.subscribe("smartcar/control/#", 1);
  }

  gyro.update(); 

}

void detectObstacle() {
  const auto frontDistance = front.getDistance();
  const auto backDistance = back.getDistance();

  // When distance is `0` it means there's no obstacle detected
  //When car is within an obstacle range of 0-1.5 meters, it stops
  if (frontDistance > 0 && frontDistance < 150){
    car.setSpeed(0); //Speed is set to zero to stop the car
    mqtt.publish("smartcar/ultrasound/front", String(frontDistance));
  }

  else if(backDistance > 0 && backDistance < 150){
    car.setSpeed(0); //Speed is set to zero to stop the car
    mqtt.publish("smartcar/infrared/back", String(backDistance));
  }
}

void stopCar() {
   car.setAngle(0);
   car.setSpeed(stopSpeed);
   const char message[] = "Obstacle detected";
   mqtt.publish("smartcar/control/stopped", message);
 } 

