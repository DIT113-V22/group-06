#include <Smartcar.h>

ArduinoRuntime arduinoRuntime;
BrushedMotor leftMotor{arduinoRuntime, smartcarlib::pins::v2::leftMotorPins};
BrushedMotor rightMotor{arduinoRuntime, smartcarlib::pins::v2::rightMotorPins};
DifferentialControl control{leftMotor, rightMotor};

SimpleCar car(control);

const int triggerPin           = 6; // D6
const int echoPin              = 7; // D7

const int triggerPin2          = 8
const int echoPin2             = 9

const unsigned int maxDistance = 300;
const int fspeed = 50;
const int bspeed = -50;
const int rdegrees = 75;
const int ldegrees = -75;
SR04 front{arduinoRuntime, triggerPin, echoPin, maxDistance};
SR04 back{arduinoRuntime, triggerPin2, echoPin2, maxDistance};

void setup()
{
  // Setup port to receive input
  Serial.begin(9600);
  //Setup car to move 50% of its speed
  car.setSpeed(0);


}

void loop()
{
 detectObstacle();
 handleInput();
#ifdef __SMCE__
  // Avoid over-using the CPU if we are running in the emulator
  delay(1);
#endif
}

void detectObstacle() {
  const auto frontDistance = front.getDistance();
  const auto backDistance = back.getDistance();

  // When distance is `0` it means there's no obstacle detected
  //When car is within an obstacle range of 0-1.5 meters, it stops
  if ((frontDistance > 0 && frontDistance < 150) || (backDistance > 0 && backDistance < 150)) {
    car.setSpeed(0); //Speed is set to zero to stop the car

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
