#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    char hand = data.charAt(0);
    int commaIndex = data.indexOf(',');
    int val = data.substring(1, commaIndex).toInt();
    String state = data.substring(commaIndex + 1);

    int pwmValue = map(val, 0, 160, 0, 200);

    if (hand == 'L') {
      BTSerial.print("L");
      BTSerial.print(pwmValue);
      BTSerial.print(",");
      BTSerial.println(state);
      Serial.print("Sent to Slave - Left: ");
      Serial.print(pwmValue);
      Serial.print(", State: ");
      Serial.println(state);
    } else if (hand == 'R') {
      BTSerial.print("R");
      BTSerial.print(pwmValue);
      BTSerial.print(",");
      BTSerial.println(state);
      Serial.print("Sent to Slave - Right: ");
      Serial.print(pwmValue);
      Serial.print(", State: ");
      Serial.println(state);
    }
  }
}