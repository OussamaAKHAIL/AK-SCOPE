/*
This code is for the first Arduino. It controls the remote, performs the calculations, and indicates which mode we are in for the second Arduino */

#include <LCD-I2C.h> // Include LCD-I2C library for controlling the LCD
#include <Math.h> // Include math library for mathematical calculations
#include <AccelStepper.h> // Include AccelStepper library for motor control

// Initialize the I2C LCD with the appropriate address
LCD_I2C lcd(0x27, 16, 2); // Address 0x27, 16 columns, and 2 rows

// Motor 1 pin definitions
const int stepPin1 = 2; // Step pin for Motor 1
const int dirPin1 = 3;  // Direction pin for Motor 1

// Motor 2 pin definitions
const int stepPin2 = 5; // Step pin for Motor 2
const int dirPin2 = 4;  // Direction pin for Motor 2

// Create instances of AccelStepper for both motors
AccelStepper motor1(AccelStepper::DRIVER, stepPin1, dirPin1);
AccelStepper motor2(AccelStepper::DRIVER, stepPin2, dirPin2);

// Pin definitions for joystick and control buttons
int joystickXPin = A1; // Joystick X-axis pin
int joystickYPin = A0; // Joystick Y-axis pin
int joystickButtonPin = 12; // Joystick button pin
int leftButtonPin = 11; // Left button pin for mode switching
int rightButtonPin = 10; // Right button pin for scope state switching
int pindyaljoy = 9; // Pin to indicate joystick mode
int pindyalonline = 8; // Pin to indicate online mode

// Variables for mode and state management
int modeState = 0;  // 0: Normal Mode, 1: Setting Mode
int settingState = 0; // State for setting date/time
int scopeState = 0; // State for scope operation mode

// Variables for date and time
int year = 2020, month = 1, day = 1, hour = 0, minute = 0, second = 0;

// Variables for previous altitude and azimuth
float prealt = 0;
float preaz = 0;

// Define a structure to store sky object data (name, RA, Dec)
struct SkyObject {
  String name; // Name of the sky object
  float RA;    // Right Ascension
  float Dec;   // Declination
};

// Array of predefined sky objects for offline mode
SkyObject skyObjects[20] = {
  {"Sirius", 6.7525, -16.7161},
  {"Canopus", 6.3992, -52.6957},
  {"Arcturus", 14.2610, 19.1825},
  {"Vega", 18.6156, 38.7837},
  {"Capella", 5.2782, 45.9979},
  {"Rigel", 5.2423, -8.2016},
  {"Procyon", 7.6550, 5.2250},
  {"Achernar", 1.6286, -57.2368},
  {"Betelgeuse", 5.9195, 7.4071},
  {"Hadar", 14.0637, -60.3729},
  {"Altair", 19.8463, 8.8683},
  {"Aldebaran", 4.5987, 16.5092},
  {"Antares", 16.4901, -26.4320},
  {"Spica", 13.4199, -11.1613},
  {"Pollux", 7.7553, 28.0262},
  {"Fomalhaut", 22.9608, -29.6222},
  {"Deneb", 20.6905, 45.2803},
  {"Regulus", 10.1395, 11.9672},
  {"Castor", 7.5766, 31.8884},
  {"Alnair", 22.1372, -46.9601}
};

// Variable to track the currently selected sky object (offline mode)
int selectedObject = 0;

void setup() {
  // Initialize output for joystick and online mode indicators
  digitalWrite(pindyaljoy, LOW);

  // Initialize the LCD
  lcd.begin();
  lcd.display();
  lcd.backlight();

  // Initialize button pins
  pinMode(joystickButtonPin, INPUT_PULLUP); // Joystick button with pull-up resistor
  pinMode(leftButtonPin, INPUT); // Left button
  pinMode(rightButtonPin, INPUT_PULLUP); // Right button
  pinMode(pindyaljoy, OUTPUT); // Joystick mode indicator
  pinMode(pindyalonline, OUTPUT); // Online mode indicator

  // Display startup message on the LCD
  lcd.setCursor(4, 0);
  lcd.print("AK space");
  delay(600);
  lcd.setCursor(4, 1);
  lcd.print("AK-scope");
  delay(1000);
  lcd.clear();

  // Initialize states
  settingState = 0;
  scopeState = 1;

  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Check for left button press to toggle between modes
  if (digitalRead(leftButtonPin) == HIGH) {
    delay(200); // Debounce delay
    modeState = (modeState == 0) ? 1 : 0; // Toggle mode state
    lcd.clear(); // Clear the LCD
  }

  // Handle the current mode
  if (modeState == 0) {
    // Normal Mode: Display normal information
    scope_mode();
  } else if (modeState == 1) {
    // Setting Mode: Adjust date/time
    lcd.setCursor(4, 0);
    lcd.print("settings");
    delay(600);
    handleSettingMode();
  }
}

// Function to handle the setting mode
void handleSettingMode() {
  switch (settingState) {
    case 0:
      // Set Year
      while (!joystickButtonPressed()) {
        lcd.setCursor(0, 0);
        lcd.print("Set Year: ");
        lcd.print(year);
        if (joystickUp() && year < 2030) year++; // Increment year
        if (joystickDown() && year > 2020) year--; // Decrement year
        if (digitalRead(leftButtonPin) == HIGH) {
          modeState = 1;
          break;
        }
      }
      settingState++;
      lcd.clear();
      delay(200);
      break;
    case 1:
      // Set Month
      while (!joystickButtonPressed()) {
        lcd.setCursor(0, 0);
        lcd.print("Set Month: ");
        lcd.print(month);
        if (joystickUp() && month < 12) month++; // Increment month
        if (joystickDown() && month > 1) month--; // Decrement month
        if (digitalRead(leftButtonPin) == HIGH) {
          modeState = 1;
          break;
        }
      }
      settingState++;
      lcd.clear();
      delay(200);
      break;
    case 2:
      // Set Day
      while (!joystickButtonPressed()) {
        lcd.setCursor(0, 0);
        lcd.print("Set Day: ");
        lcd.print(day);
        if (joystickUp() && day < 31) day++; // Increment day
        if (joystickDown() && day > 1) day--; // Decrement day
        if (digitalRead(leftButtonPin) == HIGH) {
          modeState = 1;
          break;
        }
      }
      settingState++;
      lcd.clear();
      delay(200);
      break;
    case 3:
      // Set Hour
      while (!joystickButtonPressed()) {
        lcd.setCursor(0, 0);
        lcd.print("Set Hour: ");
        lcd.print(hour);
        if (joystickUp() && hour < 23) hour++; // Increment hour
        if (joystickDown() && hour > 0) hour--; // Decrement hour
        if (digitalRead(leftButtonPin) == HIGH) {
          modeState = 1;
          break;
        }
      }
      settingState++;
      lcd.clear();
      delay(200);
      break;
    case 4:
      // Set Minute
      while (!joystickButtonPressed()) {
        lcd.setCursor(0, 0);
        lcd.print("Set Minute: ");
        lcd.print(minute);
        if (joystickUp() && minute < 59) minute++; // Increment minute
        if (joystickDown() && minute > 0) minute--; // Decrement minute
        if (digitalRead(leftButtonPin) == HIGH) {
          modeState = 1;
          break;
        }
      }
      settingState++;
      lcd.clear();
      delay(200);
      break;
    case 5:
      // Set Second
      while (!joystickButtonPressed()) {
        lcd.setCursor(0, 0);
        lcd.print("Set Second: ");
        lcd.print(second);
        if (joystickUp() && second < 59) second++; // Increment second
        if (joystickDown() && second > 0) second--; // Decrement second
        if (digitalRead(leftButtonPin) == HIGH) {
          modeState = 1;
          break;
        }
      }
      settingState = 0; // Reset to year setting after seconds
      modeState = 0; // Go back to Normal Mode
      lcd.clear();
      break;
  }
}

// Function to check if the joystick is moved up
bool joystickUp() {
  int yValue = analogRead(joystickYPin); // Read Y-axis value
  if (yValue > 400) {
    delay(200); // Debounce delay
    return true; // Joystick moved up
  }
  return false;
}

// Function to check if the joystick is moved down
bool joystickDown() {
  int yValue = analogRead(joystickYPin); // Read Y-axis value
  if (yValue < 600) {
    delay(200); // Debounce delay
    return true; // Joystick moved down
  }
  return false;
}

// Function to check if the joystick button is pressed
bool joystickButtonPressed() {
  if (digitalRead(joystickButtonPin) == LOW) {
    delay(200); // Debounce delay
    return true; // Joystick button pressed
  }
  return false;
}

// Function to handle offline mode (sky object selection and calculation)
void handleOfflineMode() {
  lcd.setCursor(3, 0);
  lcd.print(skyObjects[selectedObject].name); // Display the name of the selected sky object
  
  // Scroll through the list of sky objects using the joystick
  if (joystickUp() && selectedObject < 19) {
    selectedObject++; // Move to next sky object
    lcd.clear();
  }
  
  if (joystickDown() && selectedObject > 0) {
    selectedObject--; // Move to previous sky object
    lcd.clear();
  }
  
  // When joystick button is pressed, select the object and call the calculation function
  if (joystickButtonPressed()) {
    calculation();
  }
}

// Convert degrees to radians
float degreesToRadians(float degrees) {
  return degrees * PI / 180.0;
}

// Convert radians to degrees
float radiansToDegrees(float radians) {
  return radians * 180.0 / PI;
}

// Calculate Greenwich Sidereal Time (GST)
float calculateGST(int year, int month, int day, int hour, int minute, int second) {
  float UT = hour - 7 + minute - 15 / 60.0 + second / 3600.0; // Convert time to Universal Time
  
  // Calculate the number of days since the epoch
  int yTemp = year + (month + 9) / 12;
  float d = 367 * year - (7 * yTemp) / 4 + (275 * month) / 9 + day - 730530;
  
  // Calculate GST using the formula
  float GST = 6.697374558 + 0.06570982441908 * d + 1.00273790935 * UT;
  GST = fmod(GST, 24.0); // Ensure GST is within 24 hours
  return GST;
}

// Calculate Local Sidereal Time (LST)
float calculateLST(float gst, float longitude) {
  float LST = gst + longitude / 15.0; // Add longitude to GST to get LST
  LST = fmod(LST, 24.0); // Ensure LST is within 24 hours
  return LST;
}

// Calculate altitude and azimuth
void calculateAltAz(float ra, float dec, float lat, float lst, float &alt, float &az) {
  float HA = fmod((lst * 15.0 - ra * 15.0), 360.0); // Calculate Hour Angle
  if (HA < 0) {
    HA += 360.0; // Ensure HA is positive
  }
  HA = degreesToRadians(HA); // Convert HA to radians
  dec = degreesToRadians(dec); // Convert declination to radians
  lat = degreesToRadians(lat); // Convert latitude to radians

  // Calculate altitude
  float sinAlt = (sin(dec) * sin(lat)) + (cos(dec) * cos(lat) * cos(HA));
  alt = asin(sinAlt);

  // Calculate azimuth
  float cosAz = (sin(dec) - (sin(alt) * sin(lat))) / (cos(alt) * cos(lat));
  cosAz = constrain(cosAz, -1, 1); // Clip to avoid domain errors
  az = acos(cosAz);

  alt = radiansToDegrees(alt); // Convert altitude to degrees
  az = radiansToDegrees(az);   // Convert azimuth to degrees

  if (sin(HA) > 0) {
    az = 360.0 - az; // Adjust azimuth based on the hour angle
  }
}

// Function to handle the calculation of altitude and azimuth
float calculation() {
  float latitude = 30.25;  // Latitude for Agadir
  float longitude = -9.36; // Longitude for Agadir
  float RA = skyObjects[selectedObject].RA; // Right Ascension of the selected object
  float Dec = skyObjects[selectedObject].Dec; // Declination of the selected object
  
  // Display calculation message on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calculating...");
  
  // Calculate GST and LST
  float gst = calculateGST(year, month, day, hour, minute, second);
  float lst = calculateLST(gst, longitude);

  // Calculate altitude and azimuth
  float alt, az;
  calculateAltAz(RA, Dec, latitude, lst, alt, az);
  
  // Format and display the results
  char buffer[10] = ""; // Buffer to hold the formatted output
  sprintf(buffer, "%d°%d°", (int)az, (int)alt); // Convert az and alt to integers and format them
  Serial.println(buffer); // Print the result as one string

  // Display the results on the LCD
  lcd.clear();
  lcd.print("az: ");
  lcd.print(az);
  lcd.setCursor(0, 1);
  lcd.print("alt: ");
  lcd.print(alt);
  
  delay(2000); // Show results for 2 seconds before returning
  lcd.clear();
  return az, alt; // Return azimuth and altitude
}

// Function to handle the scope's mode operations
void scope_mode() {
  switch (scopeState) {
    case 1:
      // Offline Mode
      while (digitalRead(rightButtonPin) == 1) {
        digitalWrite(pindyaljoy, LOW); // Turn off joystick mode indicator
        digitalWrite(pindyalonline, LOW); // Turn off online mode indicator
        handleOfflineMode(); // Handle offline mode operations
        if (digitalRead(leftButtonPin) == HIGH) {
          modeState = 0; // Exit to Normal Mode
          break;
        }
        if (digitalRead(rightButtonPin) == 0) {
          scopeState = 2; // Switch to Online Mode
          delay(200);
          break;
        }
      }
      break;
    case 2:
      // Online Mode
      lcd.setCursor(2, 0);
      lcd.print("online mode: ");
      lcd.setCursor(0, 1);
      lcd.print("use the software");
      while (digitalRead(rightButtonPin) == 1) {
        digitalWrite(pindyaljoy, LOW); // Turn off joystick mode indicator
        digitalWrite(pindyalonline, HIGH); // Turn on online mode indicator
        if (digitalRead(leftButtonPin) == HIGH) {
          modeState = 0; // Exit to Normal Mode
          break;
        }
        if (digitalRead(rightButtonPin) == 0) {
          scopeState = 3; // Switch to Joystick Mode
          delay(200);
          break;
        }
      }
      break;
    case 3:
      // Joystick Mode
      lcd.setCursor(1, 0);
      lcd.print("joystick mode");
      while (digitalRead(rightButtonPin) == 1) {
        digitalWrite(pindyaljoy, HIGH); // Turn on joystick mode indicator
        digitalWrite(pindyalonline, LOW); // Turn off online mode indicator
        if (digitalRead(leftButtonPin) == HIGH) {
          modeState = 0; // Exit to Normal Mode
          break;
        }
        if (digitalRead(rightButtonPin) == 0) {
          scopeState = 1; // Switch to Offline Mode
          digitalWrite(pindyaljoy, LOW); // Turn off joystick mode indicator
          delay(200);
          break;
        }
      }
      break;
  }
}