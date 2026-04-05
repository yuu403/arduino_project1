# ===== Python側：受信・可視化・保存 =====

import serial
import matplotlib.pyplot as plt
import csv
from datetime import datetime

# ==== 設定 ====
PORT = 'COM3'   # ← Windowsの場合（Macは '/dev/tty.usbmodem...'）
BAUD = 9600

ser = serial.Serial(PORT, BAUD)

data = []
avg_data = []
max_points = 100  # 表示する最大データ数

# CSVファイル作成
filename = f"sensor_log_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv"

with open(filename, 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(["Time", "Raw", "Average"])

    plt.ion()  # リアルタイム描画ON

    while True:
        try:
            line = ser.readline().decode().strip()
            val = int(line)

            data.append(val)

            # 移動平均（直近10個）
            window = data[-10:]
            avg = sum(window) / len(window)
            avg_data.append(avg)

            # データ数制限
            if len(data) > max_points:
                data.pop(0)
                avg_data.pop(0)

            # CSV保存
            writer.writerow([datetime.now(), val, avg])

            # グラフ更新
            plt.clf()
            plt.title("Light Sensor Real-Time Graph")
            plt.xlabel("Time")
            plt.ylabel("Value")

            plt.plot(data, label="Raw Data")
            plt.plot(avg_data, label="Moving Average")

            plt.legend()
            plt.pause(0.01)

        except Exception as e:
            print("Error:", e)