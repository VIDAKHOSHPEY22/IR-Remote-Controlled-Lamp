#include <IRremote.h>

const int relayPin = 3;
const int irPin = 11;
const unsigned long targetCode = 0xBA45FF00;
bool lightState = false;
unsigned long lastPressTime = 0;

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  Serial.begin(9600);
  IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK);
  Serial.println("IR Ready - Press the programmed button");
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long now = millis();
    
    if (IrReceiver.decodedIRData.decodedRawData == targetCode && now - lastPressTime > 250) {
      lightState = !lightState;
      digitalWrite(relayPin, lightState ? LOW : HIGH);
      Serial.println(lightState ? "ON" : "OFF");
      lastPressTime = now;
    }
    
    IrReceiver.resume();
  }
}