/* Arduino n°1 : remote, calculs et IHM */
#include <LCD_I2C.h>
#include <AccelStepper.h>
#include <Wire.h>

LCD_I2C lcd(0x27, 16, 2);

const int stepPin1 = 2, dirPin1 = 3;
const int stepPin2 = 5, dirPin2 = 4;
AccelStepper motor1(AccelStepper::DRIVER, stepPin1, dirPin1);
AccelStepper motor2(AccelStepper::DRIVER, stepPin2, dirPin2);

int joystickXPin = A1, joystickYPin = A0;
int joystickButtonPin = 12;
int leftButtonPin = 11, rightButtonPin = 10;
int pindyaljoy = 9, pindyalonline = 8;

int modeState = 0, settingState = 0, scopeState = 0;
int year = 2020, month = 1, day = 1, hour = 0, minute = 0, second = 0;
float prealt = 0, preaz = 0;

/* ---- Suivi (following mode) : variables et constantes ---- */
volatile bool tick = false;
ISR(TIMER1_COMPA_vect) { tick = true; }   // interruption 1 Hz

#define ALT_MAX 50.0          // Limitation mécanique du systeme
const float i_Alt = 4.0;      // rapport de reduction axe Alt
const float i_Az  = 4.0;      // rapport de reduction axe Az
const float latitude_g  = 30.25;
const float longitude_g = -9.36;
bool followingActive = false;

struct SkyObject { String name; float RA; float Dec; };
SkyObject skyObjects[20] = {
  {"Sirius", 6.7525, -16.7161}, {"Canopus", 6.3992, -52.6957},
  {"Arcturus", 14.2610, 19.1825}, {"Vega", 18.6156, 38.7837},
  {"Capella", 5.2782, 45.9979}, {"Rigel", 5.2423, -8.2016},
  {"Procyon", 7.6550, 5.2250}, {"Achernar", 1.6286, -57.2368},
  {"Betelgeuse", 5.9195, 7.4071}, {"Hadar", 14.0637, -60.3729},
  {"Altair", 19.8463, 8.8683}, {"Aldebaran", 4.5987, 16.5092},
  {"Antares", 16.4901, -26.4320}, {"Spica", 13.4199, -11.1613},
  {"Pollux", 7.7553, 28.0262}, {"Fomalhaut", 22.9608, -29.6222},
  {"Deneb", 20.6905, 45.2803}, {"Regulus", 10.1395, 11.9672},
  {"Castor", 7.5766, 31.8884}, {"Alnair", 22.1372, -46.9601}
};
int selectedObject = 0;

/* ---- Configuration Timer1 a 1 Hz (16 MHz / 1024 / 15624 = 1 Hz) ---- */
void setupTimer1_1Hz() {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A  = 15624;                          // 1 Hz
  TCCR1B |= (1 << WGM12);                  // mode CTC
  TCCR1B |= (1 << CS12) | (1 << CS10);     // prescaler 1024
  TIMSK1 |= (1 << OCIE1A);                 // autorise interruption Compare A
  interrupts();
}

void incrementClock() {
  second++;
  if (second >= 60) { second = 0; minute++; }
  if (minute >= 60) { minute = 0; hour++; }
  if (hour   >= 24) { hour   = 0; day++; }
  if (day    >  31) { day    = 1; month++; }
  if (month  >  12) { month  = 1; year++; }
}

void setup() {
  digitalWrite(pindyaljoy, LOW);
  lcd.begin(); lcd.display(); lcd.backlight();
  pinMode(joystickButtonPin, INPUT_PULLUP);
  pinMode(leftButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT_PULLUP);
  pinMode(pindyaljoy, OUTPUT);
  pinMode(pindyalonline, OUTPUT);
  lcd.setCursor(4,0); lcd.print("AK space"); delay(600);
  lcd.setCursor(4,1); lcd.print("AK-scope"); delay(1000); lcd.clear();
  settingState = 0; scopeState = 1;

  /* Configuration des moteurs pour le suivi */
  motor1.setMaxSpeed(800);
  motor1.setAcceleration(400);
  motor2.setMaxSpeed(800);
  motor2.setAcceleration(400);

  setupTimer1_1Hz();
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(leftButtonPin) == HIGH) {
    delay(200); modeState = (modeState == 0) ? 1 : 0; lcd.clear();
  }
  if (modeState == 0) { scope_mode(); }
  else if (modeState == 1) {
    lcd.setCursor(4,0); lcd.print("settings");
    delay(600); handleSettingMode();
  }
}

void handleSettingMode() {
  switch (settingState) {
    case 0: while (!joystickButtonPressed()) {
        lcd.setCursor(0,0); lcd.print("Set Year: "); lcd.print(year);
        if (joystickUp() && year < 2030) year++;
        if (joystickDown() && year > 2020) year--;
        if (digitalRead(leftButtonPin) == HIGH) { modeState = 1; break; }
      } settingState++; lcd.clear(); delay(200); break;
    case 1: while (!joystickButtonPressed()) {
        lcd.setCursor(0,0); lcd.print("Set Month: "); lcd.print(month);
        if (joystickUp() && month < 12) month++;
        if (joystickDown() && month > 1) month--;
        if (digitalRead(leftButtonPin) == HIGH) { modeState = 1; break; }
      } settingState++; lcd.clear(); delay(200); break;
    case 2: while (!joystickButtonPressed()) {
        lcd.setCursor(0,0); lcd.print("Set Day: "); lcd.print(day);
        if (joystickUp() && day < 31) day++;
        if (joystickDown() && day > 1) day--;
        if (digitalRead(leftButtonPin) == HIGH) { modeState = 1; break; }
      } settingState++; lcd.clear(); delay(200); break;
    case 3: while (!joystickButtonPressed()) {
        lcd.setCursor(0,0); lcd.print("Set Hour: "); lcd.print(hour);
        if (joystickUp() && hour < 23) hour++;
        if (joystickDown() && hour > 0) hour--;
        if (digitalRead(leftButtonPin) == HIGH) { modeState = 1; break; }
      } settingState++; lcd.clear(); delay(200); break;
    case 4: while (!joystickButtonPressed()) {
        lcd.setCursor(0,0); lcd.print("Set Minute: "); lcd.print(minute);
        if (joystickUp() && minute < 59) minute++;
        if (joystickDown() && minute > 0) minute--;
        if (digitalRead(leftButtonPin) == HIGH) { modeState = 1; break; }
      } settingState++; lcd.clear(); delay(200); break;
    case 5: while (!joystickButtonPressed()) {
        lcd.setCursor(0,0); lcd.print("Set Second: "); lcd.print(second);
        if (joystickUp() && second < 59) second++;
        if (joystickDown() && second > 0) second--;
        if (digitalRead(leftButtonPin) == HIGH) { modeState = 1; break; }
      } settingState = 0; modeState = 0; lcd.clear(); break;
  }
}

bool joystickUp()   { return (analogRead(joystickYPin) > 400) ? (delay(200), true) : false; }
bool joystickDown() { return (analogRead(joystickYPin) < 600) ? (delay(200), true) : false; }
bool joystickButtonPressed() {
  return (digitalRead(joystickButtonPin) == LOW) ? (delay(200), true) : false;
}

void handleOfflineMode() {
  lcd.setCursor(3,0); lcd.print(skyObjects[selectedObject].name);
  if (joystickUp() && selectedObject < 19) { selectedObject++; lcd.clear(); }
  if (joystickDown() && selectedObject > 0) { selectedObject--; lcd.clear(); }
  if (joystickButtonPressed()) {
    calculation();
    followingActive = true;
    prealt = 0; preaz = 0;
    lcd.clear(); lcd.setCursor(2,0); lcd.print("Following...");
    lcd.setCursor(0,1); lcd.print(skyObjects[selectedObject].name);
    while (followingActive) {
      followingLoop();
      if (digitalRead(leftButtonPin) == HIGH) {
        followingActive = false;
        motor1.stop(); motor2.stop();
        lcd.clear();
        delay(200);
        break;
      }
      if (digitalRead(rightButtonPin) == 0) {
        followingActive = false;
        motor1.stop(); motor2.stop();
        lcd.clear();
        delay(200);
        break;
      }
    }
  }
}

float degreesToRadians(float d) { return d * PI / 180.0; }
float radiansToDegrees(float r) { return r * 180.0 / PI; }

float calculateGST(int year, int month, int day, int hour, int minute, int second) {
  float UT = hour - 7 + minute - 15 / 60.0 + second / 3600.0;
  int yTemp = year + (month + 9) / 12;
  float d = 367 * year - (7 * yTemp) / 4 + (275 * month) / 9 + day - 730530;
  float GST = 6.697374558 + 0.06570982441908 * d + 1.00273790935 * UT;
  return fmod(GST, 24.0);
}

float calculateLST(float gst, float longitude) {
  float LST = gst + longitude / 15.0;
  return fmod(LST, 24.0);
}

void calculateAltAz(float ra, float dec, float lat, float lst, float &alt, float &az) {
  float HA = fmod((lst * 15.0 - ra * 15.0), 360.0);
  if (HA < 0) HA += 360.0;
  HA = degreesToRadians(HA);
  dec = degreesToRadians(dec);
  lat = degreesToRadians(lat);
  float sinAlt = sin(dec)*sin(lat) + cos(dec)*cos(lat)*cos(HA);
  alt = asin(sinAlt);
  float cosAz = (sin(dec) - sin(alt)*sin(lat)) / (cos(alt)*cos(lat));
  cosAz = constrain(cosAz, -1, 1);
  az = acos(cosAz);
  alt = radiansToDegrees(alt); az = radiansToDegrees(az);
  if (sin(HA) > 0) az = 360.0 - az;
}

float calculation() {
  float latitude = 30.25, longitude = -9.36;
  float RA = skyObjects[selectedObject].RA;
  float Dec = skyObjects[selectedObject].Dec;
  lcd.clear(); lcd.setCursor(0,0); lcd.print("Calculating...");
  float gst = calculateGST(year, month, day, hour, minute, second);
  float lst = calculateLST(gst, longitude);
  float alt, az; calculateAltAz(RA, Dec, latitude, lst, alt, az);
  char buffer[10] = "";
  sprintf(buffer, "%d°%d°", (int)az, (int)alt);
  Serial.println(buffer);
  lcd.clear(); lcd.print("az: "); lcd.print(az);
  lcd.setCursor(0,1); lcd.print("alt: "); lcd.print(alt);
  prealt = alt; preaz = az;
  delay(2000); lcd.clear();
  return az, alt;
}

/* ---- Boucle de suivi declenchee par l'interruption Timer1 (1 Hz) ---- */
void followingLoop() {
  if (tick) {
    tick = false;
    // 1. Recalcul du temps sideral
    incrementClock();           // +1 s sur horloge interne
    float gst = calculateGST(year, month, day, hour, minute, second);
    float lst = calculateLST(gst, longitude_g);
    // 2. Recalcul Alt/Az
    float newAlt, newAz;
    float ra  = skyObjects[selectedObject].RA;
    float dec = skyObjects[selectedObject].Dec;
    calculateAltAz(ra, dec, latitude_g, lst, newAlt, newAz);
    // 3. Verification limitation mecanique (Alt <= 50°)
    if (newAlt > ALT_MAX) {
      motor1.stop(); motor2.stop();
      lcd.clear(); lcd.setCursor(0,0); lcd.print("Alt > 50: STOP");
      followingActive = false;
      return;
    }
    // 4. Delta par rapport a la position precedente
    float dAlt = newAlt - prealt;
    float dAz  = newAz  - preaz;
    // 5. Conversion en micro-pas
    long stepsAlt = (long)((dAlt / 1.8) * 32 * i_Alt);
    long stepsAz  = (long)((dAz  / 1.8) * 32 * i_Az);
    // 6. Commande differentielle (rampe douce)
    motor1.move(stepsAlt);
    motor2.move(stepsAz);
    prealt = newAlt;
    preaz  = newAz;
  }
  motor1.run();
  motor2.run();
}

void scope_mode() {
  switch (scopeState) {
    case 1: // Offline
      while (digitalRead(rightButtonPin) == 1) {
        digitalWrite(pindyaljoy, LOW); digitalWrite(pindyalonline, LOW);
        handleOfflineMode();
        if (digitalRead(leftButtonPin) == HIGH) { modeState = 0; break; }
        if (digitalRead(rightButtonPin) == 0)   { scopeState = 2; delay(200); break; }
      } break;
    case 2: // Online
      lcd.setCursor(2,0); lcd.print("online mode: ");
      lcd.setCursor(0,1); lcd.print("use the software");
      while (digitalRead(rightButtonPin) == 1) {
        digitalWrite(pindyaljoy, LOW); digitalWrite(pindyalonline, HIGH);
        if (digitalRead(leftButtonPin) == HIGH) { modeState = 0; break; }
        if (digitalRead(rightButtonPin) == 0)   { scopeState = 3; delay(200); break; }
      } break;
    case 3: // Joystick
      lcd.setCursor(1,0); lcd.print("joystick mode");
      while (digitalRead(rightButtonPin) == 1) {
        digitalWrite(pindyaljoy, HIGH); digitalWrite(pindyalonline, LOW);
        if (digitalRead(leftButtonPin) == HIGH) { modeState = 0; break; }
        if (digitalRead(rightButtonPin) == 0)   { scopeState = 1; digitalWrite(pindyaljoy, LOW); delay(200); break; }
      } break;
  }
}
