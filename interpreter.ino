/* 
**ALL THIS CODE WILL BE ON THE BOAT ARDUINO**

FUNCTIONS: 

throttle(float speed): 
	INPUT: float value (percentage between 0.00 and 1.00)
	OUTPUT: PWM directly to the dataline of the motor

	QUESTIONS:
		- Who is doing the converting from joystick forward/backward to float percentage 
		(joystick arduino or boat arduino)
	

steer(float percentage):
	INPUT: float percentage (0.00 to 1.00, 0.500 is nuetral).
		   This percentage comes pretty much straight from joystick (conditioned to percentage).
	OUTPUT: PWM signal directly to the data line of the Servo

	NOTES: See exact servo datasheet, but most say that 1ms pulse is 0 degree position and 2ms is 180 degree.
		   So the pulses will be somewhere in there.
		   Also note that the direction of the servo wont directly lead to the direction of the turn, because
		   of the push-pull mechanic of the servo setup.
*/

#include <Servo.h>

void throttle(float throttlePercentage) {
	/*	
		BEFORE SETUP: 
			Servo esc;
		IN THE SETUP:
			esc.attach(PWM PIN OF CHOICE); -> INITIALIZES PWM PIN TO WRITE 
			esc.writeMicroseconds(1000);   -> KEEPS ESC AT MINIMUM THROTTLE WHILE NOT USED
			delay(2000);				   -> ALLOWS ESC TO INITIALIZE
	*/

	if (throttlePercentage > 1.00 || throttlePercentage < 0.00) { // OUT OF RANGE INPUT
		esc.writeMicroseconds(1000); // STALLS MOTOR
		delay(20 - throttlePercentage + 1); // AFTER THROTTLE PULSE, WE WAIT FOR THE REMAINDER OF THE 20ms CYCLE
	} 
	else {
		esc.writeMicroseconds((throttlePercentage * 1000) + 1000); // SENDS PWM TO PIN BASED ON INPUT
		delay(19); // WAITS 20MS (50Hz CYCLE LENGTH)
	}
}

void steer(float steerPercentage) {		
	/*	
		BEFORE SETUP: 
			Servo servo;
		IN THE SETUP:
			servo.attach(PWM PIN OF CHOICE); -> INITIALIZES PWM PIN TO WRITE 
			servo.writeMicroseconds(1000);   -> KEEPS SERVO AT MINIMUM THROTTLE WHILE NOT USED
			delay(2000);				     -> ALLOWS SERVO TO INITIALIZE
	*/

	if (steerPercentage > 1.00 || steerPercentage < 0.00) { // OUT OF RANGE INPUT
		servo.writeMicroseconds(1000); // WRITES SERVO TO ZERO DEGREES
		delay(19);
	}
	else {
		// NEED TO FIGURE OUT THE GEOMETRY FOR SERVO OUTPUT
		servo.writeMicroseconds((steerPercentage * 1000) + 1000);
		delay(20 - steerPercentage + 1); // AFTER SERVO PULSE, WE WAIT FOR THE REMAINEDER OF THE 20ms CYCLE
	}
}
