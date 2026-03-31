#  Arduino Portfolio

## 概要
Arduinoを用いた開発プロジェクトをまとめたポートフォリオです。  
基礎から応用まで、段階的にスキルを習得していく過程を重視しています。

---

##  使用環境

- ELEGOO UNO R3（Arduino Uno互換機）
- Arduino IDE

---

##  スキル
- Arduino（C/C++）
- デジタル入出力制御
- アナログ入力
- 時間制御（millis）
- 状態管理

---

##  作品一覧

| No | プロジェクト名 | 内容 | 主な技術 |
|----|--------------|------|----------|
| 1 | [LED点滅（基礎）](./LED_01) | delayを使った基本的なLED点滅 | digitalWrite / delay |
| 2 | [非同期LED制御](./LED_02) | millisを使った非ブロッキング処理 | millis / 時間管理 |
| 3 | [スイッチ連動LED制御](./LED_switch) | ボタンでLED制御＋状態管理 | INPUT_PULLUP / トグル制御 |
| 4 | [信号機制御](./LED_03) | 赤・黄・緑LEDで信号機を再現 | 状態遷移 / millis |
| 5 | [歩行者ボタン付き信号機](./LED_04) ⭐ | 入力＋状態遷移の統合制御 | イベント処理 / 設計力 |
| 6 | [歩行者信号](./LED_05) ⭐ | 車＋人の連動制御 | 状態設計 |
| 7 | [光量調整信号](./LED_06) ⭐⭐ | センサ＋PWM制御 | 環境適応 |

---

##  設計の流れ
1. 出力制御
2. 時間制御
3. 入力処理
4. 状態遷移
5. イベント制御
6. 複合システム（歩行者信号）
7. 環境適応（光量制御）

---

##  ディレクトリ構成
arduino_project1/
│
├── LED_01/
│ ├── LED_01.ino
│ └── README.md
│
├── LED_02/
│ ├── LED_02.ino
│ └── README.md
│
├── LED_switch/
│ ├── LED_switch.ino
│ └── README.md
│
├── LED_03/
│ ├── LED_03.ino
│ └── README.md
│
├── LED_04/
│ ├── LED_04.ino
│ └── README.md
│
├── LED_05/
│ ├── LED_05.ino
│ └── README.md
│
├── LED_06/
│ ├── LED_06.ino
│ └── README.md
│
└── README.md


##  補足
本ポートフォリオは、組み込み開発の基礎から設計力の習得を目的として作成した。  
ELEGOO UNO R3を使用し、Arduino Uno互換環境で動作確認を行っている。
