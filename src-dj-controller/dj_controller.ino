#include "Midi.h"
#include "Controls.h"

void setup() {
  Serial.begin(115200);

  pinMode(18, INPUT_PULLUP);
}

void loop() {
  Serial.print("Button value : ");
  Serial.println(potentiometerRead(18));
  Serial.println(buttonRead(19));
  delay(100);
}
