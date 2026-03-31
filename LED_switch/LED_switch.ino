unsigned long startTime = 0;
bool ledState = false;
bool switchState = false;
bool lastswitchState = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(3, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(11, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(3) == LOW) {  // 押すとLOW
    if (!lastswitchState) switchState = !switchState;
    lastswitchState = true;
  } else {
    lastswitchState = false;
  }

  if (switchState){
    unsigned long now = millis();

    if (now - startTime >= 1000) {  // 1秒経過
      ledState = !ledState;         //
      digitalWrite(7, ledState);
      startTime = now;  // 更新
    }
  } else {
    digitalWrite(7, LOW);
    ledState = false;
    startTime = millis();
  }
}
