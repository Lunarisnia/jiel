#pragma once

class Time {
  public:
    Time() = delete;

    [[nodiscard]] static double GetTime();
};
