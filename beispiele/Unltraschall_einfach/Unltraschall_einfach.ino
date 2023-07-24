#include <Arduino.h>

int MOTOR_LINKS_1 = 9;
int MOTOR_LINKS_2 = 5;
int MOTOR_RECHTS_1 = 10;
int MOTOR_RECHTS_2 = 6;

int ultrasonic_power_pin = 11;    //plus Pol vom Ultraschallsensors
int ultrasonic_trigger_pin = 7;   //trigger pin vom Ultraschallsensors
int ultrasonic_echo_pin = 8;      //echo pin des Ultraschallsensors

float ultrasonic_sensor_read_distance_cm() {
  digitalWrite(ultrasonic_trigger_pin, LOW);
  delayMicroseconds(5);
  digitalWrite(ultrasonic_trigger_pin, HIGH);
  delayMicroseconds(10);

  digitalWrite(ultrasonic_trigger_pin, LOW);

  long duration_us = pulseIn(ultrasonic_echo_pin, HIGH);   //Echo Puls Länge messen

  float measured_distance_cm = (float)duration_us *  0.034 / 2; //convert to cm
  return measured_distance_cm;
}


void setup() {
  pinMode(MOTOR_LINKS_1, OUTPUT);
  pinMode(MOTOR_LINKS_2, OUTPUT);
  pinMode(MOTOR_RECHTS_1, OUTPUT);
  pinMode(MOTOR_RECHTS_2, OUTPUT);

  pinMode(ultrasonic_trigger_pin, OUTPUT);
  pinMode(ultrasonic_echo_pin, INPUT);
  pinMode(ultrasonic_power_pin, OUTPUT);

  digitalWrite(ultrasonic_power_pin, HIGH);

  Serial.begin(9600);
}

void loop() {
float cm = ultrasonic_sensor_read_distance_cm();
Serial.print(cm);
Serial.print("\n");

}
