#include "engine.h"

#include <iostream>

Engine::Engine() { isRunning = false; }

Engine::~Engine() {
  // free up memories
  delete chip8;
  delete renderer;
}

bool Engine::initSystems(const char* title, const int width, const int height) {
  renderer = new Renderer();
  renderer->initialize(title, width, height);

  chip8 = new Chip8();

  return true;
}

void Engine::run() {
  isRunning = true;

  while (isRunning) {
    chip8->emulateCycle();

    if (chip8->getDrawFlag()) {
      processInput();
      update();
      generateOutputs();
      chip8->setDrawFlag(true);
    }
  }
}

void Engine::processInput() {
  while (SDL_PollEvent(&sdlEvent) != 0) {
    if (sdlEvent.type == SDL_QUIT) {
      isRunning = false;
    } else if (sdlEvent.type == SDL_KEYDOWN) {
      switch (sdlEvent.key.keysym.sym) {
        case SDLK_1:
          chip8->key[0x1] = 1;
          break;
        case SDLK_2:
          chip8->key[0x2] = 1;
          break;
        case SDLK_3:
          chip8->key[0x3] = 1;
          break;
        case SDLK_4:
          chip8->key[0xC] = 1;
          break;
        case SDLK_q:
          chip8->key[0x4] = 1;
          break;
        case SDLK_w:
          chip8->key[0x5] = 1;
          break;
        case SDLK_e:
          chip8->key[0x6] = 1;
          break;
        case SDLK_r:
          chip8->key[0xD] = 1;
          break;
        case SDLK_a:
          chip8->key[0x7] = 1;
          break;
        case SDLK_s:
          chip8->key[0x8] = 1;
          break;
        case SDLK_d:
          chip8->key[0x9] = 1;
          break;
        case SDLK_f:
          chip8->key[0xE] = 1;
          break;
        case SDLK_z:
          chip8->key[0xA] = 1;
          break;
        case SDLK_x:
          chip8->key[0x0] = 1;
          break;
        case SDLK_c:
          chip8->key[0xB] = 1;
          break;
        case SDLK_v:
          chip8->key[0xF] = 1;
          break;
        default:
          break;
      }
    } else if (sdlEvent.type == SDL_KEYUP) {
      switch (sdlEvent.key.keysym.sym) {
        case SDLK_1:
          chip8->key[0x1] = 0;
          break;
        case SDLK_2:
          chip8->key[0x2] = 0;
          break;
        case SDLK_3:
          chip8->key[0x3] = 0;
          break;
        case SDLK_4:
          chip8->key[0xC] = 0;
          break;
        case SDLK_q:
          chip8->key[0x4] = 0;
          break;
        case SDLK_w:
          chip8->key[0x5] = 0;
          break;
        case SDLK_e:
          chip8->key[0x6] = 0;
          break;
        case SDLK_r:
          chip8->key[0xD] = 0;
          break;
        case SDLK_a:
          chip8->key[0x7] = 0;
          break;
        case SDLK_s:
          chip8->key[0x8] = 0;
          break;
        case SDLK_d:
          chip8->key[0x9] = 0;
          break;
        case SDLK_f:
          chip8->key[0xE] = 0;
          break;
        case SDLK_z:
          chip8->key[0xA] = 0;
          break;
        case SDLK_x:
          chip8->key[0x0] = 0;
          break;
        case SDLK_c:
          chip8->key[0xB] = 0;
          break;
        case SDLK_v:
          chip8->key[0xF] = 0;
          break;
        default:
          break;
      }
    }
  }
}

void Engine::update() {
  static int nextTicks = 0;
  static uint32_t lastTicks = 0;

  while (SDL_GetTicks() < nextTicks) {
  }

  uint32_t currentTicks = SDL_GetTicks();
  nextTicks = currentTicks + 16;

  uint32_t deltaTicks = currentTicks - lastTicks;
  // Convert from milliseconds to seconds delta (* 0.001f)
  float deltaTime = deltaTicks * 0.001f;

  lastTicks = currentTicks;

  // Ensure delta time is never negative.
  if (deltaTime < 0.0f) {
    deltaTime = 0.0f;
  }

  // Limit the time delta to 0.05 seconds (about 20FPS).
  if (deltaTime > 0.05f) {
    deltaTime = 0.05f;
  }
}

void Engine::generateOutputs() {
  renderer->clear();
  renderer->render(*chip8);
  renderer->present();
}

void Engine::shutdownSystems() {
  renderer->shutdown();
  SDL_Quit();
}