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
const char topic[]  = "control_button_topic";
const char topic2[]  = "car_movement_topic";

const char ssid[] = "*";
const char pass[] = "**";

ArduinoRuntime arduinoRuntime;
BrushedMotor leftMotor(arduinoRuntime, smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(arduinoRuntime, smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control(leftMotor, rightMotor);

SimpleCar car(control);

const auto oneSecond = 1000UL;

#ifdef SMCE

const int triggerPin           = 6;
const int echoPin              = 7;
const int BACK_PIN          = 3;
const auto mqttBrokerUrl = "127.0.0.1";

#else

const auto triggerPin = 33;
const auto echoPin = 32;
const auto mqttBrokerUrl = "192.168.0.40";

#endif

const unsigned int maxDistance = 300;
const int fspeed = 50;
const int bspeed = -50;

//Change this
const int rdegrees = 75;
const int ldegrees = -75;z

SR04 front{arduinoRuntime, triggerPin, echoPin, maxDistance};
GP2Y0A21 back(arduinoRuntime, BACK_PIN);

//--------------------MQTT CONNECTIONS----------------------------------//

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, pass);
  mqtt.begin(mqttBrokerUrl, 1883, net);
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
}

void loop() {
  if (mqtt.connected()) {
    mqtt.loop();
    handleInput();
    detectObstacle();


  }

#ifdef SMCE

  // Avoid over-using the CPU if we are running in the emulator
  delay(1);

#endif

// Constantemente comprobando la llegada de mensajes

  mqtt.subscribe("/smartcar/control/#", 1);
  mqtt.onMessage([](String topic, String message) {
    if (topic == "/smartcar/control/throttle") {
      car.setSpeed(message.toInt());
    } else if (topic == "/smartcar/control/steering") {
      car.setAngle(message.toInt());
    } else {
      Serial.println(topic + " " + message);
    }
  });
  

}


//--------------------BASIC CAR MOVEMENT----------------------------------//

void detectObstacle() {
  const auto frontDistance = front.getDistance();
  const auto backDistance = back.getDistance();

  // When distance is `0` it means there's no obstacle detected
  //When car is within an obstacle range of 0-1.5 meters, it stops
  if (frontDistance > 0 && frontDistance < 150){
    car.setSpeed(0); //Speed is set to zero to stop the car
    mqtt.publish("/smartcar/ultrasound/front", frontDistance);


  }

  else if(backDistance > 0 && backDistance < 150){
    car.setSpeed(0); //Speed is set to zero to stop the car
    mqtt.publish("/smartcar/infrared/back", backDistance);
  }
}

void handleInput() {
  if(Serial.available()) {
    char input = Serial.read();
    switch(input) {
      //If input is 's', we stop the car
      case 's':
        car.setSpeed(0);
        car.setAngle(0);
        break;
      case 'f':
        
        car.setSpeed(fspeed);
        car.setAngle(0);
        break;
      case 'l':
        car.setSpeed(fspeed);
        car.setAngle(ldegrees);
        break;
      case 'b':
        car.setSpeed(bspeed);
        car.setAngle(0);
        break;
      case 'r':
        car.setSpeed(fspeed);
        car.setAngle(rdegrees);
        break;
      default:
        car.setSpeed(0);
        car.setAngle(0);
        break;
    }
  }
}


//Where in the file should we run the handleinput and detect obstacle methods.
