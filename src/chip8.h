#pragma once

#include "chip8_const.h"
#include "chip8_types.h"

class Chip8 {
 public:
  Chip8();
  ~Chip8();

  void emulateCycle();
  void debugRender();
  bool loadApplication(const char* filename);

  // Total amount of pixels: 2048
  u8 gfx[64 * 32];

  // Keyboard, HEX based keypad (0x0-0xF)
  u8 key[16];

  bool getDrawFlag() { return drawFlag; }
  void setDrawFlag(bool flag) { drawFlag = flag; }

 private:
  bool drawFlag;

  // Program counter (pc)
  u16 pc;
  u16 currentOpcode;

  // Index register I
  u16 I;

  // Stack pointer
  u16 sp;

  // CPU Registers (V0 - VF)
  u8 V[16];

  // Stack (16 levels)
  u16 stack[16];

  // Memory (size = 4k)
  u8 memory[4096];

  // Timers
  u8 delay_timer;
  u8 sound_timer;

  void init();
};
