#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // RX, TX

const int LEFT_MOTOR_PIN = 6;
const int RIGHT_MOTOR_PIN = 9;

int In1 = 5;
int In2 = 4;
int In3 = 7;
int In4 = 8;

void setup() {
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
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
          digitalWrite(LED_BUILTIN, HIGH);
        } else {
          digitalWrite(In1, HIGH);
          digitalWrite(In2, LOW);
          digitalWrite(LED_BUILTIN, LOW);
        }
        analogWrite(LEFT_MOTOR_PIN, pwmValue);
        Serial.print("Left motor speed: ");
        Serial.print(pwmValue);
        Serial.print(", State: ");
        Serial.println(state);
      } 
      else if (hand == 'R') {
        if (state.equalsIgnoreCase("B")) {
          digitalWrite(In3, HIGH);
          digitalWrite(In4, LOW);
          digitalWrite(LED_BUILTIN, HIGH);
        } else {
          digitalWrite(In3, LOW);
          digitalWrite(In4, HIGH);
          digitalWrite(LED_BUILTIN, LOW);
        }
        analogWrite(RIGHT_MOTOR_PIN, pwmValue);
        Serial.print("Right motor speed: ");
        Serial.print(pwmValue);
        Serial.print(", State: ");
        Serial.println(state);
      }
    }
  }
}