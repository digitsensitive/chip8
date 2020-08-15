#pragma once
#include <SDL.h>

#include "chip8.h"

class Renderer {
 public:
  Renderer();
  ~Renderer();

  bool isCurrentDisplayModeValid();

  bool initialize(const char *windowTitle, const int windowWidth,
                  const int windowHeight);

  void clear();
  void render(const Chip8 &c8);
  void present();

  void shutdown();

  SDL_Renderer *getSDLRenderer() { return mRenderer; }
  SDL_Window *getSDLWindow() { return mWindow; }

 private:
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;

  // Declare a structure with a description of a display mode:
  // Fields: SDL_PixelFormatEnum values, width, height, refresh rate in Hz
  // and driver-specific data
  SDL_DisplayMode current;

  const char *mWindowTitle;
  int mWindowWidth;
  int mWindowHeight;
  uint8_t screenData[32][64][3];
};
