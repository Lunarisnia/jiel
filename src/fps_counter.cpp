#include "fps_counter.hpp"

FpsCounter::FpsCounter(double updateInterval) : updateInterval(updateInterval) {}

void FpsCounter::Update(double currentTime) {
    updated = false;

    if (!initialized) {
        previousTime = currentTime;
        initialized = true;
        return;
    }

    frameTime = currentTime - previousTime;
    previousTime = currentTime;
    if (frameTime <= 0.0) {
        return;
    }

    accumulatedTime += frameTime;
    ++accumulatedFrames;

    if (accumulatedTime >= updateInterval) {
        fps = static_cast<double>(accumulatedFrames) / accumulatedTime;
        accumulatedTime = 0.0;
        accumulatedFrames = 0;
        updated = true;
    }
}

double FpsCounter::GetFps() const {
    return fps;
}

double FpsCounter::GetFrameTime() const {
    return frameTime;
}

bool FpsCounter::WasUpdated() const {
    return updated;
}
