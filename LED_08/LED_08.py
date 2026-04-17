import serial
import matplotlib.pyplot as plt
import csv
import keyboard 

PORT = 'COM3'
BAUD = 115200

ser = serial.Serial(PORT, BAUD, timeout=0.01)

time_data = []
light_data = []
brightness_data = []

MAX_POINTS = 100

with open("log.csv", "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["time", "light", "brightness", "state"])

    plt.ion()
    fig, ax = plt.subplots()

    try:
        while True:
            if plt.get_fignums() == []:
                print("ウィンドウ閉じたので終了")
                break
        
            if keyboard.is_pressed('esc'):
                print("ESCで終了")
                break

            #  データ取得（あれば）
            if ser.in_waiting > 0:
                ser.reset_input_buffer()  # ← これが最重要
                line = ser.readline().decode(errors='ignore').strip()

                if line:
                    try:
                        t, light, bright, state = line.split(",")

                        time_data.append(int(t))
                        light_data.append(int(light))
                        brightness_data.append(float(bright))

                        writer.writerow([t, light, bright, state])

                        # データ制限
                        if len(light_data) > MAX_POINTS:
                            time_data.pop(0)
                            light_data.pop(0)
                            brightness_data.pop(0)

                    except:
                        pass

            #  ← 常に描画する（重要）
            ax.clear()
            ax.plot(light_data, label="Light")
            ax.plot([b*4 for b in brightness_data], label="Brightness") #スケール統一
            ax.set_ylim(0, 1023)
            ax.legend()

            plt.pause(0.02)  # ← 安定版

    except KeyboardInterrupt:
        print("Ctrl+Cで終了")

    finally:
        ser.close()
        print("シリアルポート閉じました")