#include "application.hpp"
#include <cstdlib>

#include <SDL3/SDL.h>
#include <fmt/base.h>
#include <glad/gl.h>

int main() {
    Application app{};
    app.Init();
}
