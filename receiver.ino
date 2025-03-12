// test for receiver arduino (boat)
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

// defines RF24 object (from RF24.h)
// (CE PIN, CSN PIN)
RF24 radio(7,8);

// for linking transmitter and receiver (must be same)
const byte address[6] = "00001";

void setup() {
	
	Serial.begin(9600);
	while(!Serial) {} // wait for serial

	bool begin = radio.begin();
    if (begin) Serial.println("Begin Successful");
    else Serial.println("Begin Not Succesful");	

	radio.setPALevel(RF24_PA_LOW); // low power for test
	radio.setPayloadSize(sizeof(payload));
	radio.openReadingPipe(1, address);
	radio.startListening();
}

void loop() {
	 if (radio.available()) {              // is there a payload? get the pipe number that received it
        uint8_t bytes = radio.getPayloadSize();  // get the size of the payload
        radio.read(&payload, bytes);             // fetch payload from FIFO
        Serial.print("Received ");
        Serial.println(payload);  // print the payload's value
    }
}
