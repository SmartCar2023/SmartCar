#include <Arduino.h>
#include <Servo.h>

int ML1 = 9;      // Gleichstrommotor Links
int ML2 = 5;      // Gleichstrommotor Links
int MR1 = 10;     // Gleichstrommotor Rechts
int MR2 = 6;      // Gleichstrommotor Rechts

int LSR = 3;      //Lichtschranke rechtes Rad !!!ACGHTUNG NACH BAUPLAN SIND LINKS UND RECHTS VERTAUSCHT!!!
int LSL = 2;      //Lichtschranke linkes Rad !!!ACGHTUNG NACH BAUPLAN SIND LINKS UND RECHTS VERTAUSCHT!!!
int signalR = 0;  //Variabel für LSR
int signalL = 0;  //Variabel für LSL
int LED_PIN = 4;  //LED Pin der Gabellichtschrankenplatine

int SERVO_PIN = 12;               //Servo Pin
Servo servo;                      //erstelle Servo Objekt
int pos = 0;                      //Variabel für Servo Position
int servo_mittel_position = 135;  //Trial and error Wert zwischen 0 und 180 bei dem der Ultraschallsensor nach vorne zeigt

int ultrasonic_power_pin = 11;    ///Plus Pol des Ultraschallsensors
int ultrasonic_trigger_pin = 7;   //trigger pin vom Ultraschallsensors
int ultrasonic_echo_pin = 8;      //echo pin vom Ultraschallsensors


// trim() Funktion Variabeln

float motor_korrektur_faktor_rechts_after_trim = 1.00;    //WERTE DÜRFEN NIEMALS 1 ÜBERSCHREITEN. Dies sind Korrekturfaktoren die zusätzlich zum Trim aufgerechnet werden
float motor_korrektur_faktor_links_after_trim = 1.00;     //Sollte nach dem Trim() das car immer noch eine Kurve fahren bitte hier korrigieren. Faktor ist immer >= 1. Bsp. bei Linkskurve faktor rechts verkleinern

float faktor_motor_rechts = 1.00; //Nicht ändern
float faktor_motor_links = 1.00; //Nicht ändern

int previous_right = 0; //Nicht ändern
int previous_left = 0; //Nicht ändern
int counter_right = 0; //Nicht ändern
int counter_left = 0; //Nicht ändern
unsigned long start_time;

void setup()
{
  // define PINs
  
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);
  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);

  Serial.begin(9600);

  ultrasonic_sensor_init();
  
  trim();

  servo_init();
  servo_set_degree(servo_mittel_position);
}

void loop() {
          
    float distance_to_object = ultrasonic_sensor_read_distance_cm();

    if (distance_to_object > 30) {
    drive_forward(180, 180);
    }
    
    else if (distance_to_object < 30) {

    halt_motors();
    
    servo_set_degree(180);
    delay(500);
    float distance_to_object_left = ultrasonic_sensor_read_distance_cm();
    delay(100);

    servo_set_degree(100);
    delay(500);
    float distance_to_object_right = ultrasonic_sensor_read_distance_cm();
    delay(100);

    servo_set_degree(servo_mittel_position);

    if (distance_to_object_left < distance_to_object_right) {
        drive_rotate_right(100);
    }
    else if (distance_to_object_right < distance_to_object_left) {
        drive_rotate_left(100);
    }
    delay(400);

    }
}

// define callable functions

void drive_forward(int speed_motor_left, int speed_motor_right) {
    speed_motor_left = speed_motor_left * faktor_motor_links;
    speed_motor_right = speed_motor_right * faktor_motor_rechts;

    analogWrite(MR1, 0);
    analogWrite(MR2, speed_motor_right);
    analogWrite(ML1, 0);
    analogWrite(ML2, speed_motor_left);
}

void drive_backward(int speed_motor_left, int speed_motor_right) {
    speed_motor_left = speed_motor_left * faktor_motor_links;
    speed_motor_right = speed_motor_right * faktor_motor_rechts;

    analogWrite(MR1, speed_motor_right);
    analogWrite(MR2, 0);
    analogWrite(ML1, speed_motor_left);
    analogWrite(ML2, 0);
}

void drive_rotate_right(int speed_motor_left) {
  speed_motor_left = speed_motor_left * faktor_motor_links;

  analogWrite(MR1, 0);
  analogWrite(MR2, 0);
  analogWrite(ML1, 0);
  analogWrite(ML2, speed_motor_left);

}

void drive_rotate_left(int speed_motor_right) {
  speed_motor_right = speed_motor_right * faktor_motor_rechts;

  analogWrite(MR1, 0);
  analogWrite(MR2, speed_motor_right);
  analogWrite(ML1, 0);
  analogWrite(ML2, 0);
}

void halt_motors() {
    analogWrite(MR1, 0);
    analogWrite(MR2, 0);
    analogWrite(ML1, 0);
    analogWrite(ML2, 0);
}

void trim() {

  //assign variables for script - MOTORS MUST BE DEFINED ELSEWHERE

  pinMode(LSL, INPUT);
  pinMode(signalL, OUTPUT);
  pinMode(LSR, INPUT);
  pinMode(signalR, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  float faktor_motor_rechts_trim;
  float faktor_motor_links_trim;

  //script begin

  digitalWrite(LED_PIN, HIGH);

  int speeds_to_test[] = {100, 150, 200, 255};
  for (int i = 0; i < 4; i++) {
    int speed = speeds_to_test[i];

    int l_speed = speed * faktor_motor_links;
    int r_speed = speed * faktor_motor_rechts;
    
    drive_forward(l_speed, r_speed);

    start_time = millis();
    
    while (millis() - start_time < 700) {
      int current_right = digitalRead(LSR);
      int current_left = digitalRead(LSL);

      if (current_right == 1 && previous_right == 0) {
        counter_right++;
        Serial.print(counter_right);
        Serial.print(" = counter right\n");
      };

      if (current_left == 1 && previous_left == 0) {
        counter_left++;
        Serial.print(counter_left);
        Serial.print(" = counter left\n");
      };
      previous_right = current_right;
      previous_left = current_left;
    }

  }

  digitalWrite(LED_PIN, LOW);
  halt_motors();

  if (counter_left < counter_right) {
    faktor_motor_rechts_trim = (float)counter_left / counter_right;
    faktor_motor_links_trim = 1.00;
    Serial.print("l < r Folgend faktor links und rechts nach trim\n");
  }
  else if (counter_right < counter_left) {
    faktor_motor_rechts_trim = 1.00;
    faktor_motor_links_trim = (float)counter_right / counter_left;
    Serial.print("r < l Folgend faktor links und rechts nach trim\n");
  };

    faktor_motor_links = faktor_motor_links * motor_korrektur_faktor_links_after_trim * faktor_motor_links_trim;
    faktor_motor_rechts = faktor_motor_rechts * motor_korrektur_faktor_rechts_after_trim * faktor_motor_rechts_trim;

    Serial.print(faktor_motor_links);
    Serial.print("\n");
    Serial.print(faktor_motor_rechts);


}

void servo_init() {
  servo.attach(SERVO_PIN);
}

void servo_set_degree(int degree) {
  servo.write(degree);
}

void ultrasonic_sensor_init() {
  pinMode(ultrasonic_trigger_pin, OUTPUT);
  pinMode(ultrasonic_echo_pin, INPUT);
  pinMode(ultrasonic_power_pin, OUTPUT);

  digitalWrite(ultrasonic_power_pin, HIGH);
}

float ultrasonic_sensor_read_distance_cm() {
  //send trigger Pulse

  digitalWrite(ultrasonic_trigger_pin, LOW);
  delayMicroseconds(5);
  digitalWrite(ultrasonic_trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonic_trigger_pin, LOW);

  long duration_us = pulseIn(ultrasonic_echo_pin, HIGH);   //measure echo pulse lenght

  float measured_distance_cm = (float)duration_us *  0.034 / 2; //convert to cm

  return measured_distance_cm;
}
