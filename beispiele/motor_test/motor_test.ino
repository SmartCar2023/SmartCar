#include <Arduino.h>

int ML1 = 9;      // Gleichstrommotor Links
int ML2 = 5;      // Gleichstrommotor Links
int MR1 = 10;     // Gleichstrommotor Rechts
int MR2 = 6;      // Gleichstrommotor Rechts


void setup() { 
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);
  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);
}

void loop() {
    analogWrite(MR1, 0);
    analogWrite(MR2, 200);
    analogWrite(ML1, 0);
    analogWrite(ML2, 200);  
}
