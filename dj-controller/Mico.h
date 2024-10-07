#pragma once 

enum control_type {
  POTENTIOMETER,
  BUTTON
};

struct control_mapping {
  enum control_type type;
  uint8_t index;
};

constexpr struct control_mapping mapping[]{
  { POTENTIOMETER, 0 },
  { POTENTIOMETER, 1 },
  { POTENTIOMETER, 2 },
  { POTENTIOMETER, 3 }
};

#define MIDI_CHANNEL 0xB0  // channel 1

class Mico {
private:
  Controls hardware;
  int memory[16 * 4];

public:

  Mico();

  void begin();
  void update();
};