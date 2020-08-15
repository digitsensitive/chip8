#pragma once

#include "chip8.h"
#include "renderer.h"

/*
  The Engine is a singleton class.
*/
class Engine {
 public:
  static Engine& getInstance() {
    /*
        This is a so-called "magic static" == "Meyers Singleton":
        A static local in a function is guaranteed to
        only exist once in the whole program!
    */
    static Engine instance;
    return instance;
  }

  // Disable copy constructor
  Engine(const Engine&) = delete;

  // Disable assignment operator
  Engine& operator=(const Engine&) = delete;

  Renderer& getRenderer() { return *renderer; }
  Chip8& getChip8() { return *chip8; }

  bool initSystems(const char* title, const int width, const int height);
  void run();
  void shutdownSystems();

 private:
  Engine();
  ~Engine();

  Renderer* renderer;
  Chip8* chip8;
  SDL_Event sdlEvent;

  bool isRunning;
  void processInput();
  void update();
  void generateOutputs();
};
