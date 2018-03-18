#include <LiquidCrystal.h>

const int emitterPin = 13;
const int receiverPin = A0;
int analogValue = 0;
float distance = 0;
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

void setup() {
  pinMode(emitterPin, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  digitalWrite(emitterPin, HIGH);
  delay(1);
  analogValue = analogRead(receiverPin);
  distance = 2 * pow(10, -6) * pow(EULER, 0.0166 * analogValue);
  lcd.print("Distance: ");
  lcd.setCursor(0, 1);
  lcd.print(distance, 3);
  delay(1000);
  lcd.clear();
}
