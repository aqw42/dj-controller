#include <Arduino.h>
#include "Controls.h"

#define S0_PIN 18    // D0
#define S1_PIN 19    // D1
#define S2_PIN 20    // D2 (RX)
#define S3_PIN 21    // D3 (TX)
#define SIG1_PIN 36  // A0
#define SIG2_PIN 37  // A1
#define SIG3_PIN 38  // A2
#define SIG4_PIN 39  // A3

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

#define BIT(x, n) (x & (1 << n)) >> n

void mydigitalWrite(uint8_t pin, uint8_t val)
{
  Serial.print("Pin ");
  Serial.print(pin);
  Serial.print(" writing ");
  Serial.println(val);

  digitalWrite(pin, val);
}

int myanalogRead(uint8_t pin)
{
  Serial.print("Reading on pin ");
  Serial.println(pin);

  return analogRead(pin);
}

int Controls::multiplexerRead(index_t index) {
  assert(index < 64, "Index out of bounds");

  mydigitalWrite(S0_PIN, BIT(index, 0));
  mydigitalWrite(S1_PIN, BIT(index, 1));
  mydigitalWrite(S2_PIN, BIT(index, 2));
  mydigitalWrite(S3_PIN, BIT(index, 3));

  return myanalogRead(SIG1_PIN + (index / 16));
}


int Controls::potentiometer(index_t index) {
  int value = multiplexerRead(index);

  if (memory[index] > value + 2 || memory[index] < value - 2)
    memory[index] = value;

  return map(memory[index], 150, 1023, 0, 100);
}

bool Controls::button(index_t index) {
  int value = multiplexerRead(index);

  return value > 510 ? true : false;
}
