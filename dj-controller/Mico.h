#pragma once 

enum control_type {
  POTENTIOMETER,
  BUTTON
};

struct control_mapping {
  uint8_t midino;
  enum control_type type;
  uint8_t index;
};

constexpr struct control_mapping mapping[2]{
  { 0x01, POTENTIOMETER, 0 },
  { 0x02, POTENTIOMETER, 1 }
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