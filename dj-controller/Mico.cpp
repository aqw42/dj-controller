#include <Arduino.h>
#include "Midi.h"
#include "Controls.h"
#include "Mico.h"

Mico::Mico() {
  memset(memory, 0, sizeof(memory));
}

void Mico::begin() {
  hardware.begin();
}

void Mico::update() {
  for (const struct control_mapping &control : mapping) {
    int value = 0;
    switch (control.type) {
      case POTENTIOMETER:
        value = hardware.potentiometer(control.index);
        break;

      case BUTTON:
        value = hardware.button(control.index);
        break;
    }

    if (value != memory[control.index]) {
      controlChange(MIDI_CHANNEL, control.midino, value);
      memory[control.index] = value;
    }
  }
}