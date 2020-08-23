#include "renderer.h"

#include "../icon.inl"

Renderer::Renderer() {
  mWindow = nullptr;
  mRenderer = nullptr;
}

Renderer::~Renderer() {}

/**
 * Validation of the current display mode.
 */
bool Renderer::isCurrentDisplayModeValid() {
  // Returns 0 on success or a negative error code on failure
  int currentDisplayModeReturnValue = SDL_GetCurrentDisplayMode(0, &current);

  if (currentDisplayModeReturnValue != 0) {
    return false;
  } else {
    return true;
  }
}

/**
 * Initialize the renderer with the window properties.
 */
bool Renderer::initialize(const char *windowTitle, const int windowWidth,
                          const int windowHeight) {
  // Set the classes private window properties
  mWindowSettings.title = windowTitle;
  mWindowSettings.width = windowWidth;
  mWindowSettings.height = windowHeight;

  // Returns zero on success or a negative error code on failure
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("SDL_Init failed: %s\n", SDL_GetError());
    return false;
  }

  if (!isCurrentDisplayModeValid()) {
    printf("Validation of current display mode failed: %s\n", SDL_GetError());
    return false;
  };

  // Create our window with title, position, size and flags
  mWindow = SDL_CreateWindow(mWindowSettings.title, SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, mWindowSettings.width,
                             mWindowSettings.height, SDL_WINDOW_BORDERLESS);

  // Check if we have a window
  if (mWindow == nullptr) {
    return false;
  }

  // Init window Icon
  SDL_Surface *iconSurface =
      SDL_CreateRGBSurfaceFrom(icon_rgba, 64, 64, 32, 64 * 4, 0x000000ff,
                               0x0000ff00, 0x00ff0000, 0xff000000);

  SDL_SetWindowIcon(mWindow, iconSurface);
  SDL_FreeSurface(iconSurface);

  // Check if we have a renderer
  if (mRenderer == nullptr) {
    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
  }

  return true;
}

void Renderer::clear() {
  SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
  SDL_RenderClear(mRenderer);
}

void Renderer::render(const Chip8 &c8) {
  SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
  for (int y = 0; y < 32; ++y) {
    for (int x = 0; x < 64; ++x) {
      if (c8.gfx[(y * 64) + x] == 0) {
        // Disabled
        screenData[y][x][0] = screenData[y][x][1] = screenData[y][x][2] = 0;

      } else {
        // Enabled
        screenData[y][x][0] = screenData[y][x][1] = screenData[y][x][2] = 255;

        for (int dy = 0; dy < 20; ++dy) {
          for (int dx = 0; dx < 20; ++dx) {
            SDL_RenderDrawPoint(mRenderer, x * 20 + dx, y * 20 + dy);
          }
        }
      }
    };
  };
}

void Renderer::present() { SDL_RenderPresent(mRenderer); }

/**
 * Destroy renderer and window in the case of a shutdown of the program.
 */
void Renderer::shutdown() {
  if (mRenderer) {
    SDL_DestroyRenderer(mRenderer);
  }
  if (mWindow) {
    SDL_DestroyWindow(mWindow);
  }
}
