#include <Servo.h>

// حساس الموجات
const int trigger_pin = 6;
const int echo_pin = 3;

// المحركات DC
int in1 = 2, in2 = 5;
int in3 = 10, in4 = 12;
int in5 = 4, in6 = 7;
int in7 = 8, in8 = 13;

// السيرفو
Servo servo;
int servoPin = 11;

// مسافة ووقت
long duration;
int distance;
int servoAngle = 90;
bool increasing = true;

void setup() {
  Serial.begin(9600);
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  int motorPins[] = {in1, in2, in3, in4, in5, in6, in7, in8};
  for (int i = 0; i < 8; i++) pinMode(motorPins[i], OUTPUT);

  servo.attach(servoPin);
  servo.write(servoAngle);
}

// ========== الحلقة الرئيسية ==========
void loop() {
  // حركة للأمام 30 ثانية
  moveForward();
  timedRunWithObstacleCheck(30000);

  // حركة للخلف 60 ثانية
  moveBackward();
  timedRunWithObstacleCheck(60000);

  // يمين ويسار بالتناوب 60 ثانية
  alternateRightLeft(60000);

  stopMotors();
  delay(1000); // راحة قبل إعادة الدورة
}

// ========== وظائف الحس والتفاعل ==========
void timedRunWithObstacleCheck(unsigned long durationMs) {
  unsigned long start = millis();
  while (millis() - start < durationMs) {
    measureDistance();
    if (distance <= 10) {
      Serial.println("⚠️ عائق قريب - تغيير الاتجاه");
      stopMotors();
      changeServoDirection();
      delay(1000);
      moveBackward();
      delay(2000); // يتراجع شوي
      moveForward(); // يرجع للحركة السابقة
    }
    updateServoSweep();
    delay(100); // تقليل سرعة التحديث
  }
}

void alternateRightLeft(unsigned long durationMs) {
  unsigned long start = millis();
  bool right = true;

  while (millis() - start < durationMs) {
    measureDistance();
    if (distance <= 10) {
      Serial.println("⚠️ عائق أثناء التناوب - تغيير الاتجاه");
      stopMotors();
      changeServoDirection();
      delay(1000);
      moveBackward();
      delay(2000);
    }

    if (right) moveRight();
    else moveLeft();

    updateServoSweep();
    right = !right;
    delay(2000);
  }
}

void measureDistance() {
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void changeServoDirection() {
  if (servoAngle < 90) servo.write(135);
  else servo.write(45);
  // لا نستخدم sweep هنا، فقط تغيير مفاجئ
}

// ========== حركة السيرفو المستمرة ==========
void updateServoSweep() {
  if (increasing) {
    servoAngle += 1;
    if (servoAngle >= 135) increasing = false;
  } else {
    servoAngle -= 1;
    if (servoAngle <= 45) increasing = true;
  }
  servo.write(servoAngle);
}

// ========== أوامر المحركات ==========
void moveForward() {
  setMotors(HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW);
}

void moveBackward() {
  setMotors(LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH);
}

void moveRight() {
  setMotors(HIGH, LOW, HIGH, LOW, LOW, HIGH, LOW, HIGH);
}

void moveLeft() {
  setMotors(LOW, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW);
}

void stopMotors() {
  setMotors(LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW);
}

void setMotors(
  int v1, int v2, int v3, int v4,
  int v5, int v6, int v7, int v8
) {
  digitalWrite(in1, v1); digitalWrite(in2, v2);
  digitalWrite(in3, v3); digitalWrite(in4, v4);
  digitalWrite(in5, v5); digitalWrite(in6, v6);
  digitalWrite(in7, v7); digitalWrite(in8, v8);
}
