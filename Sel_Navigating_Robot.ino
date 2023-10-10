const int trig = 2;       // Chân trig của HC-SR04
const int echo = 3;       // Chân echo của HC-SR04
const int trig1 = 11;     // Chân trig của HC-SR04
const int echo1 = 12;     // Chân echo của HC-SR04
const int trig2 = 1;      // Chân trig của HC-SR04
const int echo2 = 0;      // Chân echo của HC-SR04
#define LIMIT_SWITCH_PIN 13 // Chân kết nối của công tắc hành trình

int ENA = 5;
int IN1 = 6;
int IN2 = 7;
int ENB = 10;
int IN3 = 8;
int IN4 = 9;
int i = 0;

unsigned long duration;     // Biến đo thời gian
int distance;               // Biến lưu khoảng cách
unsigned long duration1;    // Biến đo thời gian
int distance1;              // Biến lưu khoảng cách
unsigned long duration2;    // Biến đo thời gian
int distance2;              // Biến lưu khoảng cách

int speedA = 0;
int speedB = 0;

void setup() {
  // Khai báo chân OUTPUT
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);  // Cài đặt công tắc hành trình
  Serial.begin(9600);  // Khởi tạo giao tiếp Serial

  // Khai báo chân cho các cảm biến siêu âm
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
}

void loop() {
  int limit_switch_state = digitalRead(LIMIT_SWITCH_PIN);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = int(duration / 2 / 29.412);

  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = int(duration1 / 2 / 29.412);

  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = int(duration2 / 2 / 29.412);

  if (limit_switch_state == LOW) {
    i = 1;
  }

  if (i == 1) {
    if (distance > 10) {
      // Điều khiển xe đi về phía trước
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      speedA = 100; // Tốc độ động cơ A ben phai
      speedB = 80;  // Tốc độ động cơ B
    } else if (distance <= 15) {
      if (distance1 > 8) {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        speedA = 0;   // Tốc độ động cơ A
        speedB = 100; // Tốc độ động cơ B
      } else if (distance2 > 8) {
        // Điều khiển xe rẽ trái
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        speedA = 100; // Tốc độ động cơ A
        speedB = 0;   // Tốc độ động cơ B
      }
    }
  } else if (i == 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    speedA = 0; //
