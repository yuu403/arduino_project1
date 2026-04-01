// ピン設定
const int BUTTON = 3;
const int RED = 9;
const int YELLOW = 10;
const int GREEN = 11;

const int PED_RED = 5;
const int PED_GREEN = 6;

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

bool lastButtonState = HIGH;


void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(PED_RED, OUTPUT);
  pinMode(PED_GREEN, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long now = millis();

  // ボタン（押した瞬間だけ検出）
  bool currentButton = digitalRead(BUTTON);

  if (lastButtonState == HIGH && currentButton == LOW) {
    // 緑のときだけ反応
    if (state == GREEN_STATE) {
      state = YELLOW_STATE;
      startTime = now;
    }
  }

  lastButtonState = currentButton;

  switch (state) {
    case RED_STATE: // 赤
      setLED(HIGH, LOW, LOW);
      setPedLED(LOW, HIGH);

      if (now - startTime >= redTime) {
        startTime = now;
        state = GREEN_STATE;
      }
      break;

    case GREEN_STATE: // 緑
      setLED(LOW, LOW, HIGH);
      setPedLED(HIGH, LOW); // 歩行者は赤

      if (now - startTime >= greenTime) {
        startTime = now;
        state = YELLOW_STATE;
      }
      break;

    case YELLOW_STATE: // 黄
      setLED(LOW, HIGH, LOW);
      setPedLED(HIGH, LOW); // 歩行者は赤

      if (now - startTime >= yellowTime) {
        startTime = now;
        state = RED_STATE;
      }
      break;
  }
}

// LED制御を関数化
void setLED(int r, int y, int g) {
  digitalWrite(RED, r);
  digitalWrite(YELLOW, y);
  digitalWrite(GREEN, g);
}

// 歩行者用LED
void setPedLED(int red, int green) {
  digitalWrite(PED_RED, red);
  digitalWrite(PED_GREEN, green);
}
