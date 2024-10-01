#include <Arduino.h>
#include "Controls.h"

int multiplexerRead(uint8_t index)
{
  return analogRead(index);
}

int potentiometerRead(uint8_t index)
{
  static int memory[100];

  int value = multiplexerRead(index);
  
  if (memory[index] > value + 2 || memory[index] < value - 2)
    memory[index] = value;

  return map(memory[index], 150, 1023, 0, 100);
}

bool buttonRead(uint8_t index)
{
  int value = multiplexerRead(index);

  if (value > 510) 
    return true;
  else
    return false;
}