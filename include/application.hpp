#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>
#include <string>

struct ApplicationConfig {
    std::string title = "jiel";
    int width = 1028;
    int height = 720;
};

class Application {
  public:
    explicit Application(const ApplicationConfig& config = {});
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    [[nodiscard]] bool IsValid() const;
    [[nodiscard]] SDL_Window* GetWindow() const;
    bool PollEvent(SDL_Event& event);
    void BeginFrame();
    void EndFrame();

  private:
    bool createWindow(const ApplicationConfig& config);
    bool createOpenGLContext();

    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;
    bool imguiInitialized = false;
    bool initialized = false;
};
