#pragma once

class Chip8 {
 public:
  Chip8();
  ~Chip8();

  void emulateCycle();
  void debugRender();
  bool loadApplication(const char* filename);

  // Total amount of pixels: 2048
  unsigned char gfx[64 * 32];

  // Keyboard, HEX based keypad (0x0-0xF)
  unsigned char key[16];

  bool getDrawFlag() { return drawFlag; }
  void setDrawFlag(bool flag) { drawFlag = flag; }

 private:
  bool drawFlag;

  // Program counter (pc) (can have value from 0x000 to 0xFFF)
  unsigned short pc;
  unsigned short currentOpcode;

  // Index register I (can have a value from 0x000 to 0xFFF)
  unsigned short I;

  // Stack pointer
  unsigned short sp;

  // CPU Registers (V0 - VF)
  unsigned char V[16];

  // unsigned short = 2 bytes
  // Stack (16 levels)
  unsigned short stack[16];

  // Memory (size = 4k)
  // unsigned char = 1 byte = 8 bits = 0 to 255
  unsigned char memory[4096];

  // Timers
  unsigned char delay_timer;
  unsigned char sound_timer;

  void init();
};
