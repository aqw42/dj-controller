#include <Arduino.h>
#include "Controls.h"
#include "Mico.h"

Mico mico;

void setup() {
  Serial.begin(115200);
  mico.begin();
}

void loop() {
  mico.update();
}
