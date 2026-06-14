// Include the AccelStepper library for motor control
#include <AccelStepper.h>

// Variables for receiving and parsing serial input
String inputString = "";  // To hold the incoming string
int azimuth = 0;          // Azimuth angle
int altitude = 0;         // Altitude angle

// Pin definitions for Motor 1
const int stepPin1 = 2;   // Step pin for Motor 1
const int dirPin1 = 3;    // Direction pin for Motor 1
int prexx = 0;            // Previous altitude for online mode
int prezz = 0;            // Previous azimuth for online mode

// Pin definitions for Motor 2
const int stepPin2 = 5;   // Step pin for Motor 2
const int dirPin2 = 4;    // Direction pin for Motor 2
int prealt = 0;           // Previous altitude for movement calculations
int preaz = 0;            // Previous azimuth for movement calculations

// Joystick pin definitions
const int joystickXPin = A0;  // X-axis of joystick
const int joystickYPin = A1;  // Y-axis of joystick

// Pin definitions for mode selection
int pindyaljoy = 10;      // Pin for joystick mode indicator
int pindyalonline = 11;   // Pin for online mode indicator
const int threshold = 50; // Joystick sensitivity threshold

// Create instances of AccelStepper for both motors
AccelStepper motor1(AccelStepper::DRIVER, stepPin1, dirPin1);
AccelStepper motor2(AccelStepper::DRIVER, stepPin2, dirPin2);

// Motor speed and acceleration settings
const int maxSpeed = 500; // Maximum speed (steps per second)
const int accel = 500;    // Acceleration

void setup() {
  // Initialize pins
  pinMode(6, INPUT);             // Emergency stop or additional control
  pinMode(pindyaljoy, INPUT);    // Joystick mode indicator
  pinMode(pindyalonline, INPUT); // Online mode indicator
  
  // Configure motor speed and acceleration
  motor1.setMaxSpeed(maxSpeed);
  motor1.setAcceleration(accel);
  motor2.setMaxSpeed(maxSpeed);
  motor2.setAcceleration(accel);

  // Start serial communication
  Serial.begin(9600);

  // Example initial motor movement for debugging
  long steps007 = map(40 * 2, 0, 360, 0, 200 * 32); // Map initial position
  motor1.moveTo(-steps007 * 2.2); // Move motor1 to the initial position
  
  // Run motor1 to the target position while monitoring the emergency stop
  if (digitalRead(6) == HIGH) {
    while (motor1.distanceToGo() != 0) {
      motor1.run(); // Run motor1
    }
  }
}

void loop() {
  // Check if joystick mode is active
  if (digitalRead(pindyaljoy) == LOW) {
    // Handle incoming serial data for controlling motors
    if (Serial.available() > 0) {
      inputString = Serial.readStringUntil('\n'); // Read the incoming string
      Serial.println("///////////////////////////");
      Serial.println(inputString);
      Serial.println("///////////////////////////");
      
      // Parse azimuth and altitude values from the string
      int indexOfDegree1 = inputString.indexOf('°');
      int indexOfDegree2 = inputString.lastIndexOf('°');
      
      if (indexOfDegree1 != -1 && indexOfDegree2 != -1 && indexOfDegree1 != indexOfDegree2) {
        azimuth = inputString.substring(0, indexOfDegree1).toInt(); // Extract azimuth
        altitude = inputString.substring(indexOfDegree1 + 1, indexOfDegree2).toInt(); // Extract altitude

        // Print parsed values for debugging
        Serial.print("Received Azimuth: ");
        Serial.println(azimuth);
        Serial.print("Received Altitude: ");
        Serial.println(altitude);

        // Move the motors to the specified azimuth and altitude
        steptep(altitude, azimuth);

        // Reset the values after processing
        altitude = 0;
        azimuth = 0;
      }
    }
  } else if (digitalRead(pindyalonline) == HIGH && digitalRead(pindyaljoy) == LOW) {
    // Handle online mode (more complex input format)
    if (Serial.available()) {
      inputString = Serial.readString(); // Read the incoming string
      Serial.println(inputString);

      // Parse altitude and azimuth from the formatted string
      int firstDegreeIndex = inputString.indexOf('°');
      int firstMinuteIndex = inputString.indexOf('\'');
      int firstSecondIndex = inputString.indexOf('\"');
      
      String altDegrees = inputString.substring(0, firstDegreeIndex);
      String altMinutes = inputString.substring(firstDegreeIndex + 1, firstMinuteIndex);
      String altSeconds = inputString.substring(firstMinuteIndex + 1, firstSecondIndex);
      
      int secondDegreeIndex = inputString.indexOf('°', firstDegreeIndex + 1);
      int secondMinuteIndex = inputString.indexOf("\'", firstMinuteIndex + 1);
      int secondSecondIndex = inputString.indexOf("\"", firstSecondIndex + 1);
      
      String azDegrees = inputString.substring(firstSecondIndex + 1, secondDegreeIndex);
      String azMinutes = inputString.substring(secondDegreeIndex + 1, secondMinuteIndex);
      String azSeconds = inputString.substring(secondMinuteIndex + 1, secondSecondIndex);

      // Debugging: Print the parsed values
      Serial.println("Altitude:");
      int xx = altDegrees.toInt();
      xx = xx - prexx; // Calculate difference in altitude
      prexx = altDegrees.toInt();
      Serial.print("Degrees: "); Serial.println(altDegrees);
      altMinutes = altMinutes.toInt();
      Serial.print("Minutes: "); Serial.println(altMinutes);
      altSeconds = altSeconds.toInt();
      Serial.print("Seconds: "); Serial.println(altSeconds);
      
      Serial.println("Azimuth:");
      int zz = azDegrees.toInt();
      steptep(xx, zz); // Move the motors based on parsed values
    }
  } else if (digitalRead(pindyaljoy) == HIGH && digitalRead(pindyalonline) == LOW) {
    // Handle joystick control mode
    int joystickXValue = analogRead(joystickXPin); // Read X-axis value
    int joystickYValue = analogRead(joystickYPin); // Read Y-axis value

    // Control Motor 1 with the X-axis of the joystick
    if (joystickXValue < (512 - threshold)) {
      motor1.setSpeed(-maxSpeed); // Move motor1 in one direction
    } else if (joystickXValue > (512 + threshold)) {
      motor1.setSpeed(maxSpeed); // Move motor1 in the opposite direction
    } else {
      motor1.setSpeed(0); // Stop motor1
    }

    // Control Motor 2 with the Y-axis of the joystick
    if (joystickYValue < (512 - threshold)) {
      motor2.setSpeed(-maxSpeed); // Move motor2 in one direction
    } else if (joystickYValue > (512 + threshold)) {
      motor2.setSpeed(maxSpeed); // Move motor2 in the opposite direction
    } else {
      motor2.setSpeed(0); // Stop motor2
    }

    // Run both motors
    motor1.runSpeed();
    motor2.runSpeed();
  }
}

// Function to move the motors to the specified altitude and azimuth
void steptep(int a, int b) {
  a = a - prealt;  // Calculate altitude difference
  b = b - preaz;   // Calculate azimuth difference
  
  // Convert angles to motor steps
  long steps1 = map(b * 2, 0, 360, 0, 200 * 32);  // Map azimuth to motor steps
  long steps = map(a * 2, 0, 360, 0, 200 * 32);   // Map altitude to motor steps
  
  // Set target positions for the motors
  motor2.moveTo(motor2.currentPosition() + steps1 * 8.18);
  motor1.moveTo(motor1.currentPosition() + steps * 2.2);
  
  // Run the motors to their target positions
  while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0) {
    if (digitalRead(6) == LOW) {
      motor1.run(); // Run motor1
    } else if (digitalRead(6) == HIGH) {
      motor1.stop(); // Stop motor1 if emergency stop is activated
      b = 40;        // Reset azimuth
      preaz = 40;    // Reset previous azimuth
      break;         // Exit the loop
    }
    motor2.run(); // Run motor2
  }
  
  // Update previous values after movement
  prealt = a + prealt;
  preaz = b + preaz;
}