const int potPin = A0;  // Analog pin for the potentiometer
// A0 is the analog input pin connected to the potentiometer. It will read the varying voltage to control the motor speed.

const int motorPin = 9; // PWM pin for the motor driver
// Pin 9 is a PWM (Pulse Width Modulation) pin connected to the motor driver. It will control the motor speed by varying the duty cycle of the pulse.

void setup() {
  pinMode(motorPin, OUTPUT); // Set motorPin as an output
  // This configures the motorPin (pin 9) to be an output, allowing it to send signals to the motor driver.

  Serial.begin(9600);  // Start the serial communication
  // This initializes the serial communication at a baud rate of 9600, enabling communication between the Arduino and the connected computer (or serial monitor).
}

void loop() {
  int potValue = analogRead(potPin); // Read potentiometer value (0 to 1023)
  // This reads the analog voltage on pin A0 (the potentiometer's wiper) and converts it into a digital value between 0 and 1023.
  // The potentiometer adjusts the voltage between 0V and 5V, which gets mapped into this range.

  // Map potentiometer value to PWM range (0 to 255)
  int motorSpeed = map(potValue, 0, 1023, 0, 255);
  // The `map()` function scales the potentiometer value (0 to 1023) to a PWM range (0 to 255).
  // This value is then used to control the motor speed. The motorSpeed will be between 0 (off) and 255 (maximum speed).
  
  // Write the PWM value to the motor
  analogWrite(motorPin, motorSpeed);
  // The `analogWrite()` function sends the PWM signal to the motor driver, controlling the motor speed.
  // The higher the motorSpeed, the faster the motor will run, as it represents the duty cycle of the PWM signal.

  // Print the value for debugging
  Serial.print("Pot Value: ");
  Serial.print(potValue);
  Serial.print(" | Motor Speed: ");
  Serial.println(motorSpeed);
  // These `Serial.print()` and `Serial.println()` functions output the values of the potentiometer and motor speed to the Serial Monitor.
  // This helps in debugging and monitoring how the potentiometer value changes and how the motor speed is adjusted.

  delay(100);  // Small delay to stabilize
  // The delay(100) function introduces a short pause of 100 milliseconds before the loop repeats.
  // This is done to prevent the program from running too fast and overwhelming the Serial Monitor, as well as to allow time for the motor to respond.
}

