#pragma once

class FpsCounter {
  public:
    explicit FpsCounter(double updateInterval = 0.1);

    void Update(double currentTime);

    [[nodiscard]] double GetFps() const;
    [[nodiscard]] double GetFrameTime() const;
    [[nodiscard]] bool WasUpdated() const;

  private:
    double previousTime = 0.0;
    double updateInterval = 0.1;
    double accumulatedTime = 0.0;
    double fps = 0.0;
    double frameTime = 0.0;
    unsigned int accumulatedFrames = 0;
    bool initialized = false;
    bool updated = false;
};
