#include <AccelStepper.h>
#define STEPPER_MOTOR_PIN_1 8
#define STEPPER_MOTOR_PIN_2 9
#define STEPPER_MOTOR_PIN_3 10
#define STEPPER_MOTOR_PIN_4 11

AccelStepper myStepper(AccelStepper::FULL4WIRE, STEPPER_MOTOR_PIN_1, STEPPER_MOTOR_PIN_3, STEPPER_MOTOR_PIN_2, STEPPER_MOTOR_PIN_4);
void StepperRunTillPosition(uint16_t dest){
    myStepper.moveTo(dest);
    while(myStepper.distanceToGo() != 0);// poling
     // Change direction once the motor reaches target position

		myStepper.moveTo(-myStepper.currentPosition());
  	// Move the motor one step
  	myStepper.run();
}
void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT22 And MAX30100 test!"));
  while(!Serial);
 
  myStepper.setMaxSpeed(1000);
	myStepper.setAcceleration(50);
	myStepper.setSpeed(200);
	myStepper.moveTo(200);
  
}

void loop() {
  //  measurements delay
  delay(2000);

  StepperRunTillPosition(90);
}