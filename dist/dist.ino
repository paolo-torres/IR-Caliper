#include <LiquidCrystal.h>

const int receiverPin = A0; // Receives signal from IR detector
const int button = 5; // Pin for button
float rawValue = 0; // Raw analog detector value
float distance = 0; // Converted distance
float offset = 0; // For zeroing the scale, currently unused

const float A = -4.66663023063287 * pow(10, -16);
const float B = 2.20249645504622 * pow(10, -12);
const float C = -4.06168964971507 * pow(10, -9);
const float D = 3.79627885142441 * pow(10, -6);
const float E = -1.91090878085022 * pow(10, -3);
const float F = 4.97037299705855 * pow(10, -1);
const float G = -5.26622297475161 * pow(10, 1);

String mode = "Function";

// CALIBRATION LOOKUP TABLE
float calibTable[2][25] = {
  {179.2307692, 311.6923077, 406.9230769, 502.1538462, 587.6153846, 
   653.7692308, 710.1538462, 757.3846154, 793.5384615, 821.2307692, 
   843.9230769, 862.6153846, 876.0769231, 887.6153846, 896.3846154, 
   903.9230769, 910.9230769, 915.7692308, 920.3076923, 923, 
   926.1538462, 928.4615385, 930.3076923, 932.4615385, 933.8461538},
  {0, 0.5, 1, 1.5, 2, 
   2.5, 3, 3.5, 4, 4.5, 
   5, 5.5, 6, 6.5, 7, 
   7.5, 8, 8.5, 9, 9.5, 
   10, 10.5, 11, 11.5, 12}
};

LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

void setup() {
  Serial.begin(9600);
  pinMode(receiverPin, INPUT);
  pinMode(button, INPUT);
  lcd.begin(16, 2);
}

void loop() {
  rawValue = analogRead(receiverPin);
  if (mode == "Function") {
    distance = pow(EULER, A * pow(rawValue, 6) + B * pow(rawValue, 5) 
             + C * pow(rawValue, 4) + D * pow(rawValue, 3) 
             + E * pow(rawValue, 2) + F * rawValue + G);
  } else if (mode == "Lookup") {
    distance = lookUp(rawValue, calibTable);
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("r:");
  lcd.print(rawValue);
  lcd.print(" d:");
  lcd.print(distance);
  lcd.setCursor(0, 1);
  lcd.print("Mode:" + mode);
  if (digitalRead(button)) {
    if (mode == "Function") {
      mode = "Lookup";
    } else if (mode == "Lookup") {
      mode = "Function";
    }
  }
  delay(1000);
}

float lookUp(float val, float lookupTable[][25]){
  int index = 0;
  float result;
  if (val <= lookupTable[0][0]) {
    result = 0.00;
  } else if (val >= lookupTable[0][24]) {
    result = (lookupTable[1][24] - lookupTable[1][23]) 
           / (lookupTable[0][24] - lookupTable[0][23]) 
           * (val - lookupTable[0][24]) 
           + lookupTable[1][24];
  } else {
    while (val > lookupTable[0][index + 1]) {
      index++;
    }
    result = (val - lookupTable[0][index]) / (lookupTable[0][index+1] 
           - lookupTable[0][index]) * (lookupTable[1][index+1] 
           - lookupTable[1][index]) + lookupTable[1][index]; 
  }
  
  return result;
}

