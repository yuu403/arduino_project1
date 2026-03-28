// ピン設定
const int BUTTON = 3;
const int RED = 7;
const int YELLOW = 9;
const int GREEN = 11;

// 状態定義
enum State {
  RED_STATE,
  GREEN_STATE,
  YELLOW_STATE
};

State state = RED_STATE;

// 時間管理
unsigned long startTime = 0;

// 各状態の時間（ミリ秒）
const unsigned long redTime = 5000;
const unsigned long greenTime = 5000;
const unsigned long yellowTime = 2000;


void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long now = millis();

  if (digitalRead(BUTTON) == LOW) {  // 歩行者用信号
    if (!lastswitchState) {
      startTime = now;
      state = RED_STATE;
    }
    lastswitchState = true;
  } else {
    lastswitchState = false;
  }
  switch (state) {
    case RED_STATE: // 赤
      setLED(HIGH, LOW, LOW);

      if (now - startTime >= redTime) {
        startTime = now;
        state = GREEN_STATE;
      }
      break;

    case GREEN_STATE: // 緑
      setLED(LOW, HIGH, LOW);

      if (now - startTime >= greenTime) {
        startTime = now;
        state = YELLOW_STATE;
      }
      break;

    case YELLOW_STATE: // 黄
      setLED(LOW, LOW, HIGH);

      if (now - startTime >= yellowTime) {
        startTime = now;
        state = RED_STATE;
      }
      break;
  }
}

// LED制御を関数化（ここが評価ポイント）
void setLED(int red, int green, int yellow) {
  digitalWrite(RED, red);
  digitalWrite(GREEN, green);
  digitalWrite(YELLOW, yellow);
}
