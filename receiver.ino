// test for receiver arduino (boat)
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

// defines RF24 object (from RF24.h)
// (CE PIN, CSN PIN)
RF24 receiver(9,10);

// for linking transmitter and receiver (must be same)
const byte address[6] = "00001";

void setup() {
	
	Sierial.begin(9600);
	while(!Serial) {} // wait for serial

	if (!radio.begin()) { // initialize
		Serial.println("radio hardware not responding!!");
		while(1) {} // hold an infinite loop
	}

	radio.setPALevel(RF24_PA_LOW); // low power for test
	radio.setPayloadSize(sizeof(payload));
	radio.openReadingPipe(1, address);
	radio.startListening();
}

void loop() {

	uint8_t pipe;
    if (radio.available(&pipe)) {              // is there a payload? get the pipe number that received it
    	uint8_t bytes = radio.getPayloadSize();  // get the size of the payload
      	radio.read(&payload, bytes);             // fetch payload from FIFO
      	Serial.print("Received ");
      	Serial.print(bytes);  // print the size of the payload
      	Serial.print(" bytes on pipe ");
      	Serial.print(pipe);  // print the pipe number
      	Serial.print(": ");
      	Serial.println(payload);  // print the payload's value
    }
}
