// ECE 5 W25 INDEPENDENT PROJECT
// RC Boat
// Arohan Deshpande, Jack Driscoll-Natale, Aryan Gautam

// Joystick code inspired by example code from
// https://naylampmechatronics.com/img/cms/Datasheets/000036%20-%20datasheet%20KY-023-Joy-IT.pdf

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
    // Read the current values of the input pins, convert them to 0-5 V
    float x, y;
    x = analogRead(JOYSTICK_Rx) * (5.0 / 1023);
    y = analogRead(JOYSTICK_Ry) * (5.0 / 1023);

    // Debug module: Output x and y values to serial monitor
    Serial.print("X-axis: "); Serial.print(x, 2); Serial.println("V");
    Serial.print("Y-axis: "); Serial.print(y, 2); Serial.println("V");
   
    // Include deadzone in throttle inputs of 0.1 V
    if (y < 2.502 - 0.05) {
        // Throttle input, linear to y
    }

    if (x < 2.502 - 0.05) {
        // Throttle input in the leftwards direction with magnitude linear to x
        // This can be a function called throttle(), likely one that takes one argument for
        // angular speed/accel, then the function converts that to a corresponding voltage
    } else if (x > 2.502 + 0.05) {
        // Throttle input in the rightwards direction with magnitude linear to x - 2.502
    }
}
