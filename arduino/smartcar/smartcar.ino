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
const char ssid[] = "Kwabena's iPhone";
const char pass[] = "twumasi123.";

ArduinoRuntime arduinoRuntime;
BrushedMotor leftMotor(arduinoRuntime, smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(arduinoRuntime, smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control(leftMotor, rightMotor);

SimpleCar car(control);

const int triggerPin           = 6;
const int echoPin              = 7;
const int BACK_PIN          = 3;
const auto mqttBrokerUrl = "broker.mqttdashboard.com";

const unsigned int maxDistance = 300;
const int fspeed = 50;
const int bspeed = -50;

SR04 front{arduinoRuntime, triggerPin, echoPin, maxDistance};
GP2Y0A21 back(arduinoRuntime, BACK_PIN);

//--------------------MQTT CONNECTIONS----------------------------------//

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, pass);
  mqtt.begin(mqttBrokerUrl, port, net);
  Serial.println("Connecting to WiFi...");
  auto wifiStatus = WiFi.status();
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

if(mqtt.connect("arduino", "public", "public")) {
  mqtt.subscribe("/smartcar/control/#", 1);
  mqtt.onMessage([](String topic, String message) {
    static auto starttime = 0;
    static auto endtime = 0;

  
    if (topic ==  "/smartcar/control/throttle") {
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

    else if (topic == "/smartcar/control/reverse") {
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

    else if (topic == "/smartcar/control/steer-left") {
      car.setSpeed(fspeed);
      car.setAngle(message.toInt());
  
      car.setSpeed(0);
      car.setAngle(0);
    }

    else if (topic == "/smartcar/control/steer-right") {
      car.setSpeed(fspeed);
      car.setAngle(message.toInt());
  
      car.setSpeed(0);
      car.setAngle(0);
    }

    else {
      Serial.println(topic + " " + message);
    }

  });
  } 
}

void loop() {
  
  if (mqtt.connected()) {
    mqtt.loop();
    
    detectObstacle();
    //Probably need to change some stuff here
#ifdef SMCE
  // Avoid over-using the CPU if we are running in the emulator
  delay(1);

#endif


}
}

void detectObstacle() {
  const auto frontDistance = front.getDistance();
  const auto backDistance = back.getDistance();

  // When distance is `0` it means there's no obstacle detected
  //When car is within an obstacle range of 0-1.5 meters, it stops
  if (frontDistance > 0 && frontDistance < 150){
    car.setSpeed(0); //Speed is set to zero to stop the car
    mqtt.publish("/smartcar/ultrasound/front", String(frontDistance));
  }

  else if(backDistance > 0 && backDistance < 150){
    car.setSpeed(0); //Speed is set to zero to stop the car
    mqtt.publish("/smartcar/infrared/back", String(backDistance));
  }
}