#pragma once

#include "SDL3/SDL_video.h"
struct WindowSize {
    int Width;
    int Height;
};

class Application {
  private:
    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;
    bool imguiInitialized = false;

  public:
    Application();
    ~Application();

  public:
    void Init();

  private:
    void createWindow();
    void createOpenGLContext();
};
