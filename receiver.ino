// Code for receiver arduino (boat)
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Servo.h>

// defines RF24 object (from RF24.h)
// (CE PIN, CSN PIN)
RF24 radio(7,8);

// Define pin variables
const int ESC_PIN = 9;
const int STEER_PIN = 10;

// Create a Servo variable for the ESC
Servo esc;
Servo steer;

// Define throttle function
void throttle(float speed) {
	esc.writeMicroseconds(1000 + throttlePercentage * 1000); // SENDS PWM TO PIN BASED ON INPUT
	// delay(19 - throttlePercentage); // WAITS 20MS (50Hz CYCLE LENGTH)
}

// Define steer function
void steer(float steer) {
  steer.writeMicroseconds(1000 * steer);
}

// Define the DataPacket struct
struct DataPacket {
  float motorSpeed, steerMagnitude;
};

// for linking transmitter and receiver (must be same)
const byte address[6] = "00001";

void setup() {
	
	Serial.begin(9600);
	while(!Serial) {} // wait for serial

	bool begin = radio.begin();
    if (begin) Serial.println("Begin Successful");
    else Serial.println("Begin Not Succesful");	

	radio.setPALevel(RF24_PA_LOW); // low power for test
	radio.setPayloadSize(sizeof(DataPacket));
	radio.openReadingPipe(1, address);
	radio.startListening();

  // Throttle attachments + setup
  esc.attach(ESC_PIN); // INITIALIZES PWM PIN TO WRITE 
	esc.writeMicroseconds(1000);   // KEEPS ESC AT MINIMUM THROTTLE WHILE NOT USED
	delay(4000);				   // ALLOWS ESC TO INITIALIZE

  // Steer attachments + setup
  steer.attach(STEER_PIN);

}

void loop() {
  DataPacket joystick;
	if (radio.available()) {              // is there data? get the pipe number that received it
    uint8_t bytes = radio.getPayloadSize();  // get the size of the data
    radio.read(&joystick, bytes);             // fetch payload from FIFO 

    // Store received values in new variables
    float motorSpeed = joystick.motorSpeed;
    float steerMagnitude = joystick.steerMagnitude;

    // Print the received values
    Serial.print("Received: ");
    Serial.print(motorSpeed);  Serial.print(", "); Serial.println(steerMagnitude);

  }



}
