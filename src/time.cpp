#include "time.hpp"
#include "SDL3/SDL_timer.h"
double Time::GetTime() {
    return static_cast<double>(SDL_GetTicks()) / 1000.0f;
}
