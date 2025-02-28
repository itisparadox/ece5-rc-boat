// ECE 5 W25 INDEPENDENT PROJECT
// RC Boat
// Arohan Deshpande, Jack Driscoll-Natale, Aryan Gautam

// Joystick code inspired by example code from
// https://naylampmechatronics.com/img/cms/Datasheets/000036%20-%20datasheet%20KY-023-Joy-IT.pdf

// Will need to import function files
/* ***THIS IS PUSHED TO THE HANDHELD ARDUINO*** */
#include "interpreter.ino"

// Declare and initialize joystick input pins
const int JOYSTICK_Rx = A0;
const int JOYSTICK_Ry = A1;

void setup() {
    // Connect the axis pins to the joystick microcontroller
    pinMode(JOYSTICK_Rx, INPUT);
    pinMode(JOYSTICK_Ry, INPUT);
    
    // (0,0) on joystick is at top left of joystick module

    Serial.begin(115200);
}

void loop() {
    // Read the current values of the input pins, convert them to values 0.00—1.00 for the
    // throttle() and steer() input parameters
    float x, y;
    x = analogRead(JOYSTICK_Rx) * (1.0 / 1023);
    y = analogRead(JOYSTICK_Ry) * (1.0 / 1023);

    // Debug module: Output scaled x and y values to serial monitor
    Serial.print("X-axis: "); Serial.print(x, 2); Serial.println("V");
    Serial.print("Y-axis: "); Serial.print(y, 2); Serial.println("V");
   
    // Include deadzone in throttle inputs of 0.05 (subtracted explicitly for clarity)
    if (y < 0.500 - 0.025) {
        throttle(y); // Throttle input, linear to y
    }

    if (x < 0.500 - 0.025) {
        steer(x); // Steer to the right
    } else if (x > 0.500 + 0.025) {
        steer(x); // Steer to the left
    }
}
