# Code Explanation:
The sketch begins by including the newly installed AccelStepper libr    ary.

    #include <AccelStepper.h>
First, the Arduino pins are defined, to which the DRV8825’s STEP and DIR pins are connected. The ``motorInterfaceType`` is also set to 1. (1 means an external stepper driver with step and direction pins).

    // Define pin connections
    const int dirPin = 2;
    const int stepPin = 3;

    // Define motor interface type
    #define motorInterfaceType 1

Following that, an instance of the stepper library named ``myStepper`` is created.

    AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);
	
In the setup function, the maximum permitted speed of the motor is set to 1000 (the motor will accelerate up to this speed when we run it). The acceleration/deceleration rate is then set to add acceleration and deceleration to the stepper motor’s movements.

The desired constant speed is set to 200. And, because the NEMA 17 takes 200 steps per turn, the target position is also set to 200.

	void setup() {
		myStepper.setMaxSpeed(1000);
		myStepper.setAcceleration(50);
		myStepper.setSpeed(200);
		myStepper.moveTo(200);
	}

In the loop function, an ``if`` statement is used to determine how far the motor needs to travel (by reading the ``distanceToGo property``) before reaching the target position (set by ``moveTo``). When the ``distanceToGo`` reaches zero, the motor is rotated in the opposite direction by setting the ``moveTo`` position to negative of its current position.

At the bottom of the loop, you’ll notice that the ``run()`` function is called. This is the most critical function because the stepper will not move unless this function is executed.

	void loop() {
		if (myStepper.distanceToGo() == 0) 
			myStepper.moveTo(-myStepper.currentPosition());
	
		myStepper.run();
	}

Source: https://lastminuteengineers.com/drv8825-stepper-motor-driver-arduino-tutorial/
