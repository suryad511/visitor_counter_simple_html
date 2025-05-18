# ESP8266 Visitor Counter with Firebase and LCD

This project is a people counter using an **ESP8266 (NodeMCU)** microcontroller, two **PIR sensors**, an **LCD (I2C)** screen, and **Firebase Realtime Database**. The system tracks the number of people entering and exiting a room and updates this information both on an LCD display and in a Firebase database. A simple HTML page is provided to display live visitor data via a browser.

---

## Features

- Counts visitors entering (`PIR1`) and exiting (`PIR2`)
- Displays current room count on 16x2 LCD (I2C)
- Sends data to Firebase Realtime Database
- Triggers a buzzer when maximum room capacity is exceeded
- Web interface (HTML + JS) to display real-time stats from Firebase

---

## Hardware Requirements

- ESP8266 (NodeMCU)
- 2x PIR motion sensors
- 1x 16x2 LCD with I2C module
- 1x Buzzer
- Jumper wires
- Breadboard or soldered prototype board

---

## Wiring Diagram

| Component | ESP8266 Pin |
|----------|-------------|
| PIR1     | D0 (GPIO16) |
| PIR2     | D7 (GPIO12) |
| Buzzer   | D5 (GPIO14) |
| LCD SDA  | D2 (GPIO4)  |
| LCD SCL  | D1 (GPIO5)  |

*Make sure the I2C LCD address is `0x27`. Use an I2C scanner sketch if unsure.*

---

## Firebase Setup

1. Go to [Firebase Console](https://console.firebase.google.com/)
2. Create a new project
3. Enable **Realtime Database**
4. Go to **Project Settings > Service Accounts** and generate a **Database Secret** for legacy Firebase authentication
5. Use your Firebase URL and secret in the Arduino code:
   ```cpp
   #define FIREBASE_HOST "your-project-id.firebaseio.com"
   #define FIREBASE_AUTH "your-firebase-database-secret"
