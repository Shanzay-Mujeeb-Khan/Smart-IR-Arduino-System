# IR Remote Controlled LED & Buzzer System using Arduino Uno
An interactive embedded systems project that utilizes an Infrared (IR) sensor to toggle an LED and trigger acoustic feedback (Buzzer) using any household IR Remote Control.
---
## 🛠️ Components Used
* Arduino Uno Board
*  IR Receiver Sensor Module
* Green LED
* Piezo Buzzer
* Breadboard & Jumper Wires
* IR Remote Control
---
## ⚡ Circuit Wiring Summary

| Component | Pin / Terminal | Arduino Pin / Rail |
| :--- | :--- | :--- |
| **IR Receiver** | Signal (Out) | Pin 11 |
| **IR Receiver** | VCC | 5V Rail (+) |
| **IR Receiver** | GND | Ground Rail (-) |
| **LED** | Anode (+) | Pin 13 |
| **LED** | Cathode (-) | Ground Rail (-) |
| **Buzzer** | Positive (+) | Pin 8 |
| **Buzzer** | Negative (-) | Ground Rail (-) |

---
## 🧠 Key Features & Logic
* **Signal Decoding:** Uses `IRremote` library to read raw HEX signals transmitted by the IR remote control.
* **Debounce & Repeat Suppression:** Implemented `IRDATA_FLAGS_IS_REPEAT` filter to ignore continuous signal flags when holding down a button, preventing unwanted LED flickering.
* **State Toggling:** Uses Boolean state switching (`ledState = !ledState`) to keep the LED stably ON until the next single button press turns it OFF.
* **Audio Feedback:** Short 60ms pulse sent to Pin 8 for immediate tactile click sound on signal reception.
---
## 💻 Arduino C++ Code
```cpp
#include <IRremote.hpp>
const int IR_RECEIVE_PIN = 11;
const int LED_PIN = 13;
const int BUZZER_PIN = 8;
bool ledState = LOW;
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
}
void loop() {
  if (IrReceiver.decode()) {
    // Ignore repeat signals from holding down buttons
    if (!(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
      
      // Audio Beep
      digitalWrite(BUZZER_PIN, HIGH);
      delay(60);
      digitalWrite(BUZZER_PIN, LOW);
      
      // Toggle LED State
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      
      delay(250);
    }
    
    IrReceiver.resume();
  }
}
