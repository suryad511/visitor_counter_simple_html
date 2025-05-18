#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int Buzzer = 14; // D5
const int PIR1 = 16;   // D0
const int PIR2 = 12;   // D7

int masuk = 0, keluar = 0, count = 0, maks = 20;
int tunda = 500;

#define FIREBASE_HOST "---"
#define FIREBASE_AUTH "---"
#define WIFI_SSID "---"
#define WIFI_PASSWORD "---"

void upload_firebase(int in, int out, int tot) {
  Firebase.setInt("Data/Visitor in", in);
  Firebase.setInt("Data/Visitor out", out);
  Firebase.setInt("Data/Currently inside", tot);
}

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  pinMode(PIR1, INPUT);
  pinMode(PIR2, INPUT);
  pinMode(Buzzer, OUTPUT);

  digitalWrite(Buzzer, LOW);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected. IP Address: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  upload_firebase(masuk, keluar, count);

  lcd.setCursor(0, 0);
  lcd.print("JUMLAH: ");
  lcd.setCursor(11, 0);
  lcd.print("ORANG");
  lcd.setCursor(1, 1);
  lcd.print(" Kondisi Aman   ");
}

void loop() {
  bool visin = digitalRead(PIR1);
  bool visout = digitalRead(PIR2);

  if (visin && !visout) {
    masuk++;
    count = masuk - keluar;
    tone(Buzzer, 1000, 200); // short beep
    delay(tunda);
  } else if (visout && !visin) {
    keluar++;
    count = masuk - keluar;
    tone(Buzzer, 800, 200); // short beep
    delay(tunda);
  }

  upload_firebase(masuk, keluar, count);

  lcd.setCursor(8, 0);
  lcd.print(count);
  lcd.print("  "); // Clear extra digits

  if (count > maks) {
    lcd.setCursor(0, 0);
    lcd.print("TOTAL=> ");
    lcd.setCursor(8, 0);
    lcd.print(count);
    lcd.print(" ");
    lcd.setCursor(11, 0);
    lcd.print("ORANG");
    lcd.setCursor(1, 1);
    lcd.print("RUANGAN PENUH   ");
    tone(Buzzer, 2000, 500); // alarm tone
    delay(500);
  } else {
    lcd.setCursor(1, 1);
    lcd.print(" Kondisi Aman   ");
  }

  Serial.print("Currently inside = ");
  Serial.println(count);
  Serial.print("Visitor in = ");
  Serial.println(masuk);
  Serial.print("Visitor out = ");
  Serial.println(keluar);

  delay(100);
}
