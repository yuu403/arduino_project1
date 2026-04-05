// ピン設定
const int BUTTON = 3;

const int RED = 9;
const int YELLOW = 10;
const int GREEN = 11;

const int PED_RED = 5;
const int PED_GREEN = 6;

const int LIGHT_SENSOR = A0;

// 状態定義
enum State {
  RED_STATE,
  GREEN_STATE,
  YELLOW_STATE
};

State state = RED_STATE;

// 時間管理
unsigned long startTime = 0;
unsigned long sensorTime = 0;

// 各状態の時間（ミリ秒）
const unsigned long redTime = 5000;
const unsigned long greenTime = 5000;
const unsigned long yellowTime = 2000;

bool lastButtonState = HIGH;

// 明るさ平滑化用
int brightness = 0;
int prevBrightness = 0;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(PED_RED, OUTPUT);
  pinMode(PED_GREEN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  Serial.begin(9600); // デバッグ用
}

void loop() {
  unsigned long now = millis();
  unsigned long sensor_now = millis();

  int lightValue = analogRead(LIGHT_SENSOR);

  if (lightValue > 300) {
    brightness = 255;     // 明るい → 最大 
  } else {
    brightness = 10;   // 暗い → 消える
  }

  // ===== デバッグ表示（効果を見える化）=====
  if (sensor_now - sensorTime >= 100) {
    Serial.print(now);
    Serial.print(", ");
    Serial.print(lightValue);
    Serial.print(", ");
    Serial.print(brightness);
    Serial.print(", ");
    Serial.println(state);

    sensorTime = millis();
  }

  // ボタン処理
  bool currentButton = digitalRead(BUTTON);

  if (lastButtonState == HIGH && currentButton == LOW) {
    if (state == GREEN_STATE) {
      state = YELLOW_STATE;
      startTime = now;
    }
  }

  lastButtonState = currentButton;

  // 状態制御
  switch (state) {
    case RED_STATE:
      setLED(HIGH, LOW, LOW, brightness);
      setPedLED(LOW, HIGH, brightness);

      if (now - startTime >= redTime) {
        startTime = now;
        state = GREEN_STATE;
      }
      break;

    case GREEN_STATE:
      setLED(LOW, LOW, HIGH, brightness);
      setPedLED(HIGH, LOW, brightness);

      if (now - startTime >= greenTime) {
        startTime = now;
        state = YELLOW_STATE;
      }
      break;

    case YELLOW_STATE:
      setLED(LOW, HIGH, LOW, brightness);
      setPedLED(HIGH, LOW, brightness);

      if (now - startTime >= yellowTime) {
        startTime = now;
        state = RED_STATE;
      }
      break;
  }
}

// LED制御
void setLED(int r, int y, int g, int brightness) {
  analogWrite(RED, r ? brightness : 0);
  analogWrite(YELLOW, y ? brightness : 0);
  analogWrite(GREEN, g ? brightness : 0);
}

// 歩行者LED
void setPedLED(int red, int green, int brightness) {
  analogWrite(PED_RED, red ? brightness : 0);
  analogWrite(PED_GREEN, green ? brightness : 0);
}