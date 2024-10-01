#pragma once

typedef uint8_t index_t;

class Controls
{
  private:
    int memory[16 * 4];
    
    int multiplexerRead(index_t);

  public:
    Controls();
    void begin();
    int potentiometer(index_t);
    bool button(index_t);
};

