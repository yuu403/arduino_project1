# 🔌 Arduino Portfolio

## 📌 概要
Arduinoを用いた開発プロジェクトをまとめたポートフォリオです。  
基礎から応用まで、段階的にスキルを習得していく過程を重視しています。

---

## 🧑‍💻 スキル
- Arduino（C/C++）
- デジタル入出力制御
- アナログ入力
- 時間制御（millis）
- 状態管理

---

## 📂 作品一覧

| No | プロジェクト名 | 内容 | 主な技術 |
|----|--------------|------|----------|
| 1 | [LED点滅（基礎）](./Ltika_01) | delayを使った基本的なLED点滅 | digitalWrite / delay |
| 2 | [非同期LED制御](./Ltika_02) | millisを使った非ブロッキング処理 | millis / 時間管理 |
| 3 | [スイッチ連動LED制御](./Ltika_switch) | ボタンでLED制御＋状態管理 | INPUT_PULLUP / トグル制御 |
| 4 | [信号機制御](./Ltika_03) | 赤・黄・緑LEDで信号機を再現 | 状態遷移 / millis |
| 5 | [歩行者ボタン付き信号機](./Ltika_04) ⭐ | 入力＋状態遷移の統合制御 | イベント処理 / 設計力 |

---

## 📁 ディレクトリ構成
arduino_project1/
│
├── Ltika_01/
│ ├── Ltika_01.ino
│ └── README.md
│
├── Ltika_02/
│ ├── Ltika_02.ino
│ └── README.md
│
├── Ltika_switch/
│ ├── Ltika_switch.ino
│ └── README.md
│
├── Ltika_03/
│ ├── Ltika_03.ino
│ └── README.md
│
├── Ltika_04/
│ ├── Ltika_04.ino
│ └── README.md
│
└── README.md
