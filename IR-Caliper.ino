#include <LiquidCrystal.h>

const int emitterPin = 13;
const int receiverPin = 12;
float dist = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(emitterPin, OUTPUT);
  pinMode(receiverPin, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Distance: ");
}

void loop() {
  digitalWrite(emitterPinPin, HIGH);
  digitalWrite(receiverPin, HIGH);
  lcd.print(dist, DEC);
  if (dist == 100) {
    dist = 0;
  }
  dist++;
}
