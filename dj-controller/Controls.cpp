#include <Arduino.h>
#include "Controls.h"

#define S0_PIN 2    // D0
#define S1_PIN 3    // D1
#define S2_PIN 4    // D2 (RX)
#define S3_PIN 5    // D3 (TX)
#define SIG1_PIN A0  // A0
#define SIG2_PIN A1  // A1
#define SIG3_PIN A2  // A2
#define SIG4_PIN A3  // A3
#undef CONTROL_DEBUG

Controls::Controls() {
  memset(memory, 0, sizeof(memory));  
}

void Controls::begin()
{
  pinMode(SIG1_PIN, INPUT);
  pinMode(SIG2_PIN, INPUT);
  pinMode(SIG3_PIN, INPUT);
  pinMode(SIG4_PIN, INPUT);
  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);
}

#define assert(condition, message) \
    do { \
        if (!(condition)) { \
            Serial.println(message); \
            while (1); /* Halt the program */ \
        } \
    } while (0)

#define BIT(i, x) ((x >> i) % 2) 

void mydigitalWrite(uint8_t pin, uint8_t val)
{
#ifdef CONTROL_DEBUG
  Serial.print("Pin ");
  Serial.print(pin);
  Serial.print(" writing ");
  Serial.println(val);
#endif

  digitalWrite(pin, val);
}

int myanalogRead(uint8_t pin)
{
#ifdef CONTROL_DEBUG
  Serial.print("Reading on pin ");
  Serial.println(pin);
#endif

  return analogRead(pin);
}

int Controls::multiplexerRead(index_t index) {
  assert(index < 64, "Index out of bounds");

  mydigitalWrite(S0_PIN, BIT(0, index));
  mydigitalWrite(S1_PIN, BIT(1, index));
  mydigitalWrite(S2_PIN, BIT(2, index));
  mydigitalWrite(S3_PIN, BIT(3, index));

  return myanalogRead(SIG1_PIN + (index / 16));
}


int Controls::potentiometer(index_t index) {
  int value = multiplexerRead(index);

  if (memory[index] > value + 2 || memory[index] < value - 2)
    memory[index] = value;

  return map(memory[index], 0, 1023, 0, 127);
}

bool Controls::button(index_t index) {
  int value = multiplexerRead(index);

  return value > 510 ? true : false;
}
