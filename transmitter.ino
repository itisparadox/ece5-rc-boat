#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
// test for transmitter (joystick arduino)

// initializes radio object
// (CE PIN, CSN PIN)
RF24 radio(7, 8);

// pipeline address (must be identical to other transceiver)
const byte address[6] = "00001";

float payload = 0.0;

void setup() {
	
	Serial.begin(9600);
	
	while(!Serial) {} // wait for serial to start

	bool begin = radio.begin();
    if (begin) Serial.println("Begin Successful");
    else Serial.println("Begin NOT Succesful.");

	// set low for testing
	radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

	// save on transmission time by setting the radio to only transmit the
  	// number of bytes we need to transmit a float
  	radio.setPayloadSize(sizeof(payload));  // float datatype occupies 4 bytes

	radio.openWritingPipe(address); // start writing	
	radio.stopListening(); // transmitter mode

	// radio.printPrettyDetails(); // (larger) function that prints human readable data
}

void loop() {
	
	bool report = radio.write(&payload, sizeof(float));  // transmit & save the report

	 if (report) {
     	Serial.print("Transmission successful! ");  // payload was delivered
      	Serial.print("Sent: ");
      	Serial.println(payload);  // print payload sent
    } else {
      	Serial.println("Transmission failed or timed out");  // payload was not delivered
    }

	delay(1000);
}
