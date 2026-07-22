// ============================================
//   ESP32 Bluetooth RC Car — 4WD
//   Motor Driver : L298N
//   App          : Arduino Bluetooth Controller
//   Speed        : Fixed (ENA/ENB → 5V)
// ============================================

#include "BluetoothSerial.h"

// ── Bluetooth Object ──────────────────────
BluetoothSerial BT;

// ── Pin Definitions ───────────────────────
#define IN1  27   // Left  motors — Forward
#define IN2  26   // Left  motors — Backward
#define IN3  25   // Right motors — Forward
#define IN4  33   // Right motors — Backward

// ── Movement Functions ────────────────────
void moveForward() {
  digitalWrite(IN1, HIGH);  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);   digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);   digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);   digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);   digitalWrite(IN4, HIGH);
}

void stopCar() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);
}

// ── Setup ────────────────────────────────
void setup() {
  pinMode(IN1, OUTPUT);  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);  pinMode(IN4, OUTPUT);
  stopCar();
  BT.begin("ESP32_RC_Car");
  Serial.begin(9600);
  Serial.println("Bluetooth Ready — Device: ESP32_RC_Car");
}

// ── Loop ──────────────────────────────────
void loop() {
  if (BT.available()) {
    char command = BT.read();
    Serial.print("Command: ");
    Serial.println(command);

    switch (command) {
      case 'F': moveForward();  break;
      case 'B': moveBackward(); break;
      case 'L': turnLeft();     break;
      case 'R': turnRight();    break;
      case 'S': stopCar();      break;
      default: stopCar();      break; // Safety
    }
  }
}
