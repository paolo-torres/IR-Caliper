#include <LiquidCrystal.h>

const int emitterPin = 13;
const int receiverPin = 12;
float dist = 0;
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

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
