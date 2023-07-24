#include <Arduino.h>

int MOTOR_LINKS_1 = 9;
int MOTOR_LINKS_2 = 5;
int MOTOR_RECHTS_1 = 10;
int MOTOR_RECHTS_2 = 6;

void setup() {
  pinMode(MOTOR_LINKS_1, OUTPUT);
  pinMode(MOTOR_LINKS_2, OUTPUT);
  pinMode(MOTOR_RECHTS_1, OUTPUT);
  pinMode(MOTOR_RECHTS_2, OUTPUT);
}

void loop() {
  digitalWrite(MOTOR_LINKS_1, LOW);
  digitalWrite(MOTOR_LINKS_2, HIGH);
  digitalWrite(MOTOR_RECHTS_1, LOW);
  digitalWrite(MOTOR_RECHTS_2, HIGH);
}
