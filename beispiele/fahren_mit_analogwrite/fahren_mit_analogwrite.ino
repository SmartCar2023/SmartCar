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
  forward();
  delay(1000);
  backward();
  delay(1000);
}

void forward(){
  analogWrite(MOTOR_LINKS_1, 0);
  analogWrite(MOTOR_LINKS_2, 150);
  analogWrite(MOTOR_RECHTS_1, 0);
  analogWrite(MOTOR_RECHTS_2, 150);
}

void backward(){
  analogWrite(MOTOR_LINKS_1, 150);
  analogWrite(MOTOR_LINKS_2, 0);
  analogWrite(MOTOR_RECHTS_1, 150);
  analogWrite(MOTOR_RECHTS_2, 0);
}
