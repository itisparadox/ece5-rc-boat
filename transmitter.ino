#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
// test for transmitter (joystick arduino)

// initializes radio object
// (CE PIN, CSN PIN)
RF24 radio(7, 8);

// pipeline address (must be identical to other transceiver)
const byte address[6] = "00001";

// Declare and initialize joystick input pins
const int JOYSTICK_Rx = A0;
const int JOYSTICK_Ry = A1;

// Define a DataPacket struct
struct DataPacket {
  float motorSpeed, steerMagnitude;
};

void setup() {
	// Connect axis pins to the joystick microcontroller
  pinMode(JOYSTICK_Rx, INPUT);
  pinMode(JOYSTICK_Ry, INPUT);

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
  // Read axis pins
	float x, y;
  x = analogRead(JOYSTICK_Rx);
  y = analogRead(JOYSTICK_Ry);

  // Map the values and assign them to new variables
  float motorSpeed = -1 * ((y*2-1023) / 1023); // 1023 to 0 mapped to -1 to 1
  float steerMagnitude = 2 + ((x-1023) / 1023); // 0 to 1023 mapped to 1 to 2

  // Debug motorSpeed and steerMagnitude: output values
  Serial.print("Motor Speed: "); Serial.println(motorSpeed, 2);
  Serial.print("Steering Magnitude: "); Serial.println(steerMagnitude, 2);

  // Store motorSpeed and steerMagnitude in a DataPacket
  DataPacket joystickData;
  joystickData.motorSpeed = motorSpeed;
  joystickData.steerMagnitude = steerMagnitude;

  // Transmit data & save the report
	bool report = radio.write(&joystickData, sizeof(DataPacket));

	if (report) {
    Serial.print("Transmission successful! ");  // Data was sent
      Serial.print("Sent: ");
      Serial.print(joystickData.motorSpeed); Serial.print(", "); Serial.println(joystickData.steerMagnitude);
  } else {
      Serial.println("Transmission failed or timed out"); // Data was not sent
  }

  // Throttle at motorSpeed
  if (motorSpeed > 0) {
    throttle(motorSpeed);
  }

  // Steer at steerMagnitude {
    steer(steerMagnitude);
  }

	delay(1000);
}
