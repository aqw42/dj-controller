#include "Midi.h"
#include "Controls.h"

Controls control;

void setup() {
  Serial.begin(115200);
  control.begin();
}

void loop() {
  Serial.println(control.potentiometer(0));
  Serial.println(control.potentiometer(1));
  delay(100);
}
