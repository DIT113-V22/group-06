#include <MQTT.h>
#include <WiFi.h>
#ifdef SMCE
#include <OV767X.h>
#endif
#include <Smartcar.h>

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

SimpleCar car(control);

const int triggerPin           = 6;
const int echoPin              = 7;
const int BACK_PIN          = 3;
const auto mqttBrokerUrl = "broker.emqx.io";

const unsigned int maxDistance = 300;
const int fspeed = 50;
const int bspeed = -50;
const int stopSpeed = 0;

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
          if(detectObstacle()) {
            break;
          }
          car.setSpeed(fspeed);
          car.setAngle(0);
          endtime = millis();
        }
        stopCar();
        
      }

       if (topic == "smartcar/control/reverse") {
        Serial.println(topic);
        starttime = millis();
        endtime = starttime;
        while ((endtime - starttime) <= message.toInt() * 1000) {
           if(detectObstacle()) {
            break;
          }
          car.setSpeed(bspeed);
          car.setAngle(0);
          endtime = millis();
        }
        stopCar();
      }

      if (topic == "smartcar/control/steer-left") {
        
        Serial.println(topic);
        car.setSpeed(fspeed);
        car.setAngle(message.toInt());
    
        car.setSpeed(0);
        car.setAngle(0);
      }

      if (topic == "smartcar/control/steer-right") {
         
        Serial.println(topic);
        car.setSpeed(fspeed);
        car.setAngle(message.toInt());
    
        car.setSpeed(0);
        car.setAngle(0);
      }

      else {
        Serial.println(topic + " " + message);
      }
    }
  );   
}

void loop() {
  
  if (mqtt.connected()) {
    mqtt.loop();
    const auto currentTime = millis();
    static auto previousTransmission = 0UL;
    if (currentTime - previousTransmission >= 1000) {
      previousTransmission = currentTime;
      const auto distance = String(front.getDistance());
    //Probably need to change some stuff here
   
  } 
   #ifdef SMCE
      // Avoid over-using the CPU if we are running in the emulator
      delay(1);
    #endif
    
  }
  else {
    mqtt.connect("arduino", "public", "public");
    mqtt.subscribe("smartcar/control/#", 1);
  }
}

boolean detectObstacle() {
  const auto frontDistance = front.getDistance();
  const auto backDistance = back.getDistance();

  // When distance is `0` it means there's no obstacle detected
  //When car is within an obstacle range of 0-1.5 meters, it stops
  if (frontDistance > 0 && frontDistance < 150){
    //mqtt.publish("smartcar/ultrasound/front", String(frontDistance));
    return true;
    
  }

  if(backDistance > 0 && backDistance < 150){
    // mqtt.publish("smartcar/infrared/back", String(backDistance));
    return true;
  
  }
  return false;
}
 void stopCar() {
   car.setAngle(0);
   car.setSpeed(stopSpeed);
   const char message[] = "Obstacle detected";
   mqtt.publish("smartcar/control/stopped", message);
 } 

