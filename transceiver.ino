#include <SPI.h>        // Include SPI library for communication with RF module
#include <nRF24L01.h>   // Include nRF24L01 library for wireless communication
#include <RF24.h>       // Include RF24 library for controlling the radio module
#include <Servo.h>      // Include Servo library for controlling the steering servo

// Define motor control pins
#define MOTOR_PWM 9      // PWM pin for motor speed control
#define MOTOR_DIR 8      // Direction control pin for motor
#define STEERING_SERVO 6 // Pin for steering servo control

// Define joystick input pins
#define JOYSTICK_X A0    // Joystick X-axis (steering) connected to analog pin A0
#define JOYSTICK_Y A1    // Joystick Y-axis (throttle) connected to analog pin A1

// Create RF24 radio object with CE and CSN pins
// CE (Chip Enable) is connected to pin 7, used to control data transmission
// CSN (Chip Select Not) is connected to pin 8, used to enable/disable SPI communication
RF24 radio(7, 8); // CE on pin 7, CSN on pin 8

// Define communication address for RF transmission  
// This address is a unique identifier for wireless communication between modules  
// Both transmitter and receiver must use the same address for proper communication  
const byte address[6] = "00001"; // Unique address for communication

// Define a struct to store throttle and steering data
struct DataPacket {
    int throttle;  // Variable to store throttle value
    int steering;  // Variable to store steering value
};
DataPacket data;  // Create an instance of DataPacket

Servo steeringServo; // Create a Servo object for steering control

void setup() {
    pinMode(MOTOR_PWM, OUTPUT); // Set motor PWM pin as output
    pinMode(MOTOR_DIR, OUTPUT); // Set motor direction pin as output

    steeringServo.attach(STEERING_SERVO); // Attach servo to defined pin
    // Initialize serial communication at a baud rate of 9600 bits per second  
    // The baud rate determines the speed of data transfer between the Arduino and the computer  
    // 9600 is a standard baud rate, balancing speed and reliability for debugging  
    // This allows real-time monitoring of data sent and received via the Serial Monitor  
    // It is useful for troubleshooting, checking transmitted values, and ensuring correct operation 
    Serial.begin(9600); // Initialize serial communication at 9600 baud rate

    radio.begin(); // Initialize RF24 module
    radio.openWritingPipe(address); // Open writing pipe to specified address
    radio.setPALevel(RF24_PA_LOW); // Set power level for RF communication
    radio.stopListening(); // Set module to transmit mode
}

void loop() {
    data.throttle = analogRead(JOYSTICK_Y); // Read joystick Y-axis value for throttle
    data.steering = analogRead(JOYSTICK_X); // Read joystick X-axis value for steering

    radio.write(&data, sizeof(DataPacket)); // Transmit data packet via RF module

    // Print sent data to Serial Monitor for debugging
    Serial.print("Sent - Throttle: "); Serial.print(data.throttle);
    Serial.print(" Steering: "); Serial.println(data.steering);

    delay(50); // Short delay to regulate data transmission frequency
}

