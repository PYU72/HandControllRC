#include <SoftwareSerial.h>
#include <Servo.h>

//블루투스
SoftwareSerial BTSerial(2, 3); // RX, TX

//dc모터 핀
const int LEFT_MOTOR_PIN = 6;
const int RIGHT_MOTOR_PIN = 9;

int In1 = 5;
int In2 = 4;
int In3 = 7;
int In4 = 8;

//서보모터 설정
Servo myServo;
const int SERVO_PIN = 10;

void setup() {
  //dc모터 출력지정
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  
  //서보모터 설정
  myServo.attach(SERVO_PIN);
  myServo.write(90);  // 초기 위치를 중앙(90도)으로 설정

  BTSerial.begin(9600);
}

void loop() {
  if (BTSerial.available()) {
    String data = BTSerial.readStringUntil('\n');
    
    if (data.length() > 0) {
      char hand = data.charAt(0);
      int commaIndex = data.indexOf(',');
      int pwmValue = data.substring(1, commaIndex).toInt();
      String state = data.substring(commaIndex + 1);
      state.trim();

      if (hand == 'L') {
        if (state.equalsIgnoreCase("B")) {
          digitalWrite(In1, LOW);
          digitalWrite(In2, HIGH);
        } else {
          digitalWrite(In1, HIGH);
          digitalWrite(In2, LOW);
        }
        analogWrite(LEFT_MOTOR_PIN, pwmValue);
      } 
      else if (hand == 'R') {
        if (state.equalsIgnoreCase("B")) {
          digitalWrite(In3, HIGH);
          digitalWrite(In4, LOW);
        } else {
          digitalWrite(In3, LOW);
          digitalWrite(In4, HIGH);
        }
        analogWrite(RIGHT_MOTOR_PIN, pwmValue);
      }
      else if (hand == 'S') {
        if (state.equalsIgnoreCase("ON")) {
          myServo.write(180);  // 서보 모터를 180도로 회전
        } else {
          myServo.write(0);    // 서보 모터를 0도로 회전 (원래 위치로)
        }
      }
    }
  }
}