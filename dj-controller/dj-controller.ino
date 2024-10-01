#include "Midi.h"
#include "Controls.h"

Controls control;

void setup() {
  Serial.begin(115200);
  control.begin();
}

void loop() {
  Serial.print("Button value : ");
  Serial.println(control.button(0));
  Serial.println(control.potentiometer(15));
  delay(100);
}
