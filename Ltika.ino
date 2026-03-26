unsigned long startTime = 0;
bool ledState = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long now = millis();

  if (now - startTime >= 1000) {  // 1秒経過
    ledState = !ledState; 
    digitalWrite(7, ledState);
    startTime = now;  // 更新
  }
}
