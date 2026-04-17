// ===== Clean Architecture Version =====

// ピン設定
const int BUTTON = 3;

const int RED = 9;
const int YELLOW = 10;
const int GREEN = 11;

const int PED_RED = 5;
const int PED_GREEN = 6;

const int LIGHT_SENSOR = A0;

// 定数
const int LIGHT_THRESHOLD = 300;
const int BRIGHT = 255;
const int DARK = 10;

// 状態
enum State {
  RED_STATE,
  GREEN_STATE,
  YELLOW_STATE
};

State state = RED_STATE;

// 時間
unsigned long startTime = 0;
unsigned long lastSendTime = 0;

// 各状態時間
const unsigned long RED_TIME = 5000;
const unsigned long GREEN_TIME = 5000;
const unsigned long YELLOW_TIME = 2000;

// 入力状態
bool lastButtonState = HIGH;

// センサ
int lightValue = 0;
float brightness = 255;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(PED_RED, OUTPUT);
  pinMode(PED_GREEN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  Serial.begin(115200);
}

// =========================
// メインループ
// =========================
void loop() {
  unsigned long now = millis();

  updateSensor();
  updateButton(now);
  updateState(now);
  updateOutput();
  sendSerial(now);
}

// =========================
// センサ処理
// =========================
void updateSensor() {
   // センサ読み取り
  lightValue = analogRead(LIGHT_SENSOR);

  // ノイズ軽減（追加）
  lightValue = (lightValue + analogRead(LIGHT_SENSOR)) / 2;

  // 連続変化 (明るいほど明るく)
  int targetBrightness = map(lightValue, 0, 1023, DARK, BRIGHT);

  // 範囲制限
  targetBrightness = constrain(targetBrightness, DARK, BRIGHT);

  // なめらかに変化（平滑化）
  static int prevBrightness = BRIGHT;
  brightness = prevBrightness * 0.8 + targetBrightness * 0.2;
  prevBrightness = brightness;
}

// =========================
// ボタン処理
// =========================
void updateButton(unsigned long now) {
  bool current = digitalRead(BUTTON);

  if (lastButtonState == HIGH && current == LOW) {
    if (state == GREEN_STATE) {
      changeState(YELLOW_STATE, now);
    }
  }

  lastButtonState = current;
}

// =========================
// 状態更新
// =========================
void updateState(unsigned long now) {
  switch (state) {
    case RED_STATE:
      if (isTimeUp(now, RED_TIME)) {
        changeState(GREEN_STATE, now);
      }
      break;

    case GREEN_STATE:
      if (isTimeUp(now, GREEN_TIME)) {
        changeState(YELLOW_STATE, now);
      }
      break;

    case YELLOW_STATE:
      if (isTimeUp(now, YELLOW_TIME)) {
        changeState(RED_STATE, now);
      }
      break;
  }
}

// =========================
// 出力制御
// =========================
void updateOutput() {
  switch (state) {
    case RED_STATE:
      setCarLED(HIGH, LOW, LOW);
      setPedLED(LOW, HIGH);
      break;

    case GREEN_STATE:
      setCarLED(LOW, LOW, HIGH);
      setPedLED(HIGH, LOW);
      break;

    case YELLOW_STATE:
      setCarLED(LOW, HIGH, LOW);
      setPedLED(HIGH, LOW);
      break;
  }
}

// =========================
// シリアル送信
// =========================
void sendSerial(unsigned long now) {
  if (now - lastSendTime >= 80) {
    Serial.print(now);
    Serial.print(",");
    Serial.print(lightValue);
    Serial.print(",");
    Serial.print(brightness);
    Serial.print(",");
    Serial.println(getStateName());

    lastSendTime = now;
  }
}

// =========================
// ヘルパー
// =========================
bool isTimeUp(unsigned long now, unsigned long duration) {
  return (now - startTime >= duration);
}

void changeState(State newState, unsigned long now) {
  state = newState;
  startTime = now;
}

// LED制御
void setCarLED(int r, int y, int g) {
  analogWrite(RED, r ? brightness : 0);
  analogWrite(YELLOW, y ? brightness : 0);
  analogWrite(GREEN, g ? brightness : 0);
}

void setPedLED(int red, int green) {
  analogWrite(PED_RED, red ? brightness : 0);
  analogWrite(PED_GREEN, green ? brightness : 0);
}

// 状態名
const char* getStateName() {
  switch (state) {
    case RED_STATE: return "RED";
    case GREEN_STATE: return "GREEN";
    case YELLOW_STATE: return "YELLOW";
    default: return "UNKNOWN";
  }
}