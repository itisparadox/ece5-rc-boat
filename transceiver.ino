#include <SPI.h>      // Include SPI library for communication with RF module
#include <nRF24L01.h> // Include nRF24L01 library for wireless communication
#include <RF24.h>     // Include RF24 library for controlling the radio module
#include <Servo.h>    // Include Servo library for controlling the steering servo

// Define motor and servo pins
#define MOTOR_PWM 9      // PWM pin for motor speed control
#define MOTOR_DIR 8      // Direction control pin for motor
#define STEERING_SERVO 6 // Pin for steering servo control

// Define input pins
#define JOYSTICK_X A0 // 
#define JOYSTICK_Y A1

RF24 radio(7, 8); // CE, CSN pins
const byte address[6] = "00001";

struct DataPacket {
    int throttle;
    int steering;
};
DataPacket data;

Servo steeringServo;

void setup() {
    pinMode(MOTOR_PWM, OUTPUT);
    pinMode(MOTOR_DIR, OUTPUT);
    
    steeringServo.attach(STEERING_SERVO);
    Serial.begin(9600);
    
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_LOW);
    radio.stopListening();
}

void loop() {
    data.throttle = analogRead(JOYSTICK_Y);
    data.steering = analogRead(JOYSTICK_X);
    
    radio.write(&data, sizeof(DataPacket));
    
    Serial.print("Sent - Throttle: "); Serial.print(data.throttle);
    Serial.print(" Steering: "); Serial.println(data.steering);
    
    delay(50);
}

