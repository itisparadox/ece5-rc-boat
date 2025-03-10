// ECE 5 W25 INDEPENDENT PROJECT
// RC Boat
// Arohan Deshpande, Jack Driscoll-Natale, Aryan Gautam

// Joystick code inspired by example code from
// https://naylampmechatronics.com/img/cms/Datasheets/000036%20-%20datasheet%20KY-023-Joy-IT.pdf

/* ***THIS IS PUSHED TO THE HANDHELD ARDUINO*** */
#include <Servo.h>

Servo esc;
void throttle(float throttlePercentage) {
		esc.writeMicroseconds(1000 + throttlePercentage * 1000); // SENDS PWM TO PIN BASED ON INPUT
		//delay(19 - throttlePercentage); // WAITS 20MS (50Hz CYCLE LENGTH)
}

float mapFloat(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
  
}

// Declare and initialize joystick input pins
const int JOYSTICK_Rx = A0;
const int JOYSTICK_Ry = A1;
const int ESC_PIN = 9;

void setup() {
    // Connect the axis pins to the joystick microcontroller
    pinMode(JOYSTICK_Rx, INPUT);
    pinMode(JOYSTICK_Ry, INPUT);
    //pinMode(ESC_PIN, OUTPUT);
    // (0,0) on joystick is at top left of joystick module

    Serial.begin(9600);

  		esc.attach(ESC_PIN); // INITIALIZES PWM PIN TO WRITE 
			esc.writeMicroseconds(1000);   // KEEPS ESC AT MINIMUM THROTTLE WHILE NOT USED
			delay(4000);				   // ALLOWS ESC TO INITIALIZE
}

void loop() {
    // Read the current values of the input pins, convert them to values 0.00—1.00 for the
    // throttle() and steer() input parameters
    float x, y;
    x = analogRead(JOYSTICK_Rx) * (1.0 / 1023);
    y = analogRead(JOYSTICK_Ry);
    /*
    float mapFloat(float value, float fromLow, float fromHigh, float toLow, float toHigh){
      return (y - 0) * (-1 )
    }
    */ 
    float motorSpeed = -1 * ((y*2-1023) /1023);

    // Debug module: Output scaled x and y values to serial monitor
    // Serial.print("X-axis: "); Serial.print(x, 2); Serial.println("V");
    Serial.print("Y-axis: "); Serial.print(motorSpeed, 2); Serial.println("units");
 
    // Include deadzone in throttle inputs of 0.05 (subtracted explicitly for clarity)
    if (motorSpeed > 0) {
        throttle(motorSpeed); // Throttle input, linear to y
    }

  //OCR1A = 1000 + (motorSpeed * 1000);
  //delay(10);

    if (x < 0.500 - 0.025) {
        // steer(x); // Steer to the right
    } else if (x > 0.500 + 0.025) {
        // steer(x); // Steer to the left
    }
}
