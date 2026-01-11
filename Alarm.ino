#include <WiFi.h>
#include <ESP_Mail_Client.h>

/* ───────────── WIFI ───────────── */
#define WIFI_SSID "TON_WIFI"
#define WIFI_PASSWORD "MOT_DE_PASSE_WIFI"

/* ───────────── EMAIL ───────────── */
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

#define AUTHOR_EMAIL "tonmail@gmail.com"
#define AUTHOR_PASSWORD "MOT_DE_PASSE_APPLICATION"

#define RECIPIENT_EMAIL "destinataire@gmail.com"

/* ───────────── ULTRASON ───────────── */
#define TRIG_PIN 4
#define ECHO_PIN 5

/* ───────────── BUZZER ───────────── */
#define BUZZER_PIN 6

#define DISTANCE_THRESHOLD 30  // cm (variation déclenchement)

SMTPSession smtp;
float referenceDistance = 0;
bool intrusionDetected = false;

/* ───────────── FONCTIONS ───────────── */

float measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 25000);
  if (duration == 0) return 999;

  return duration * 0.034 / 2;
}

void beepAlarm() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
}

void sendIntrusionEmail() {
  SMTP_Message message;

  message.sender.name = "ESP32 Security";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "🚨 INTRUSION DETECTED";
  message.addRecipient("Owner", RECIPIENT_EMAIL);

  String textMsg = "⚠️ A door intrusion has been detected.\n"
                   "The ultrasonic sensor lost its reference distance.\n"
                   "Please check immediately.";

  message.text.content = textMsg.c_str();
  message.text.charSet = "utf-8";

  ESP_Mail_Session session;
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  smtp.connect(&session);
  MailClient.sendMail(&smtp, &message);
}

/* ───────────── SETUP ───────────── */

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  delay(2000); // Stabilisation capteur

  referenceDistance = measureDistance();
}

/* ───────────── LOOP ───────────── */

void loop() {
  float currentDistance = measureDistance();

  if (!intrusionDetected &&
      abs(currentDistance - referenceDistance) > DISTANCE_THRESHOLD) {

    intrusionDetected = true;

    beepAlarm();
    sendIntrusionEmail();
  }

  delay(500);
}
