#include <Arduino.h>

// motor input
#define IN1 5
#define IN2 18
#define IN3 19
#define IN4 21

#define MOTOR_ROUND_STEP 2048  // 2048 steps per round for 28BYJ-48
#define MOTOR_HALF_STEP 4096  // 4096 steps per round for 28BYJ-48 in half-step mode
#define ROTATION_SPEED 2  // ms per step

// half-step sequence for 28BYJ-48
void motor_control(int step) {
  switch (step) {
    case 0:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 1:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 2:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 3:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 4:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 5:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      break;
    case 6:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    case 7:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
  }
}

// rotate appointed steps clockwise
void rotateClockwise(int steps) {
  for (int i = 0; i < steps; i++) {
    motor_control(i % 8);
    delay(ROTATION_SPEED);
  }
}

// rotate appointed steps counter-clockwise
void rotateCounterClockwise(int steps) {
  for (int i = 0; i < steps; i++) {
    motor_control(7 - (i % 8));
    delay(ROTATION_SPEED);
  }
}

// rotate appointed angles clockwise or counter-clockwise
void rotateAngle(float angle, bool clockwise = true) {
  int steps = (int)(MOTOR_HALF_STEP * (angle / 360.0));
  if (clockwise) {
    rotateClockwise(steps);
  } else {
    rotateCounterClockwise(steps);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(115200);
  Serial.println("步进电机控制初始化完毕：");
  
}

void loop() {
  // rotate command example: send "w" for clockwise, "s" for counter-clockwise
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    if (cmd=="w") {
      Serial.println("顺时针旋转一圈");
      rotateAngle(360, true);
    } else if (cmd=="s") {
      Serial.println("逆时针旋转一圈");
      rotateAngle(360, false);
    } else {
      Serial.println("未知命令，请输入 w/s/a/d 来控制旋转");
    }
  }
}

