# 🚨 ESP32-C3 Door Intrusion Detector — Ultrasonic & Buzzer

This project uses an ESP32-C3 Super Mini, an HC-SR04 ultrasonic sensor,
and a buzzer to detect a door opening (intrusion).
When the ultrasonic sensor loses its reference distance (door opens),
the system triggers a sound alarm and sends an email alert.

This project is designed for home security, embedded systems learning,
and IoT alerting.

────────────────────────────────────────────────────────

📸 PREVIEW

(images/setup.jpg)
(images/alarm_triggered.jpg)

────────────────────────────────────────────────────────

🧠 FEATURES

🚪 Door intrusion detection using ultrasonic distance change  
📏 Reference distance calibration at startup  
🔊 Audible alarm with buzzer  
📧 Email alert sent automatically  
📡 Wi-Fi connectivity  
🛡️ Anti-spam protection (email sent once per intrusion)  
🧰 Clean and well-commented Arduino code  

────────────────────────────────────────────────────────

🧭 REQUIREMENTS

HARDWARE
- ESP32-C3 Super Mini
- HC-SR04 Ultrasonic Sensor
- Active or passive buzzer
- Jumper wires
- Voltage divider for ECHO pin (recommended)

SOFTWARE
- Arduino IDE
- ESP32 board support
- ESP Mail Client library

Install via Arduino Library Manager:
ESP Mail Client

────────────────────────────────────────────────────────

🔌 PIN CONFIGURATION

ESP32-C3 PINS USED

Ultrasonic TRIG  → GPIO 4  
Ultrasonic ECHO  → GPIO 5 (⚠️ 5V → use voltage divider)  
Buzzer +         → GPIO 6  
GND              → GND  
Ultrasonic VCC  → 5V  

────────────────────────────────────────────────────────

🔌 WIRING

ULTRASONIC SENSOR (HC-SR04)
VCC  → 5V  
GND  → GND  
TRIG → GPIO 4  
ECHO → GPIO 5 (via voltage divider)

BUZZER
+ → GPIO 6  
- → GND  

────────────────────────────────────────────────────────

🚀 HOW IT WORKS

1. At startup, the system measures and stores the reference distance
   (door closed).
2. The ultrasonic sensor continuously measures the distance.
3. If the distance changes beyond a defined threshold,
   the door is considered open.
4. The system:
   - Triggers the buzzer alarm
   - Sends an intrusion email alert
5. The email is sent only once per intrusion event.

────────────────────────────────────────────────────────

🚀 HOW TO RUN

1. Clone the repository:
git clone https://github.com/moh5377/Intrusion-Alarm.git

2. Open the .ino file in Arduino IDE

3. Edit Wi-Fi and email credentials in the code:
WIFI_SSID
WIFI_PASSWORD
AUTHOR_EMAIL
AUTHOR_PASSWORD (App password)
RECIPIENT_EMAIL

4. Select board:
ESP32C3 Dev Module

5. Upload the code to the ESP32-C3

────────────────────────────────────────────────────────

📧 EMAIL ALERT

SMTP Server: Gmail  
Port: 465 (SSL)  
Requires Gmail App Password  

Email subject:
🚨 INTRUSION DETECTED

Email content example:
A door intrusion has been detected.
The ultrasonic sensor lost its reference distance.
Please check immediately.

────────────────────────────────────────────────────────

🛠️ POSSIBLE IMPROVEMENTS

- Add delay before triggering alarm
- Add physical ON/OFF or arm/disarm switch
- Add OLED status display
- Add Telegram or mobile notification
- Integrate with Home Assistant

