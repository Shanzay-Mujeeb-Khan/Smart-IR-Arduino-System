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

    if (!(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
      
     
      digitalWrite(BUZZER_PIN, HIGH);
      delay(60);
      digitalWrite(BUZZER_PIN, LOW);
      
     
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      
      delay(250); 
    }
    
    IrReceiver.resume();
  }
}