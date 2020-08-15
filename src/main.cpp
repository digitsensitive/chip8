#include <stdio.h>

#include "engine.h"

// Display size
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

int modifier = 20;
bool isRunning = false;

// Window size
int displayWidth = SCREEN_WIDTH * modifier;
int displayHeight = SCREEN_HEIGHT * modifier;

Engine& engine = Engine::getInstance();

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Usage: chip-8 chip8application\n\n");
    return 1;
  }

  bool initSucceeded =
      engine.initSystems("CHIP-8", displayWidth, displayHeight);

  // Load game
  if (!engine.getChip8().loadApplication(argv[1])) {
    return 1;
  };

  if (initSucceeded) {
    engine.run();
  }

  engine.shutdownSystems();

  return 0;
}
