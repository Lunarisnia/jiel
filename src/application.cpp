#include "application.hpp"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_time.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"
#include "fmt/format.h"
#include "math/vec3.hpp"

#include <SDL3/SDL.h>
#include <array>
#include <cstdio>
#include <fmt/base.h>
#include <glad/gl.h>
#include <string>

Application::Application() = default;

constexpr WindowSize WINDOW_SIZE = {
    .Width = 1028,
    .Height = 720,
};

GLuint shaderProgram = 0;
GLuint triangleVAO = 0;
GLuint triangleVAO2 = 0;

bool checkShaderCompilation(GLuint shader, const char* name) {
    GLint compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_TRUE) {
        return true;
    }

    GLint logLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

    std::string log(static_cast<std::size_t>(logLength), '\0');
    GLsizei written = 0;
    glGetShaderInfoLog(shader, logLength, &written, log.data());
    log.resize(static_cast<std::size_t>(written));
    fmt::println(stderr, "{} shader compilation failed:\n{}", name, log);
    return false;
}

bool checkProgramLink(GLuint program) {
    GLint linked = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked == GL_TRUE) {
        return true;
    }

    GLint logLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

    std::string log(static_cast<std::size_t>(logLength), '\0');
    GLsizei written = 0;
    glGetProgramInfoLog(program, logLength, &written, log.data());
    log.resize(static_cast<std::size_t>(written));
    fmt::println(stderr, "Shader program link failed:\n{}", log);
    return false;
}

void setupDrawTriangle() {
    // clang-format off
    std::array<math::Vec3, 3> points = {
      math::Vec3(0.0f, 0.5f, 0.0f),
      math::Vec3(0.5f, -0.5f, 0.0f),
      math::Vec3(-0.5f, -0.5f, 0.0f),
    };
    std::array<math::Vec3, 3> points2 = {
      math::Vec3(0.5f, 0.5f, 0.0f),
      math::Vec3(1.0f, -0.5f, 0.0f),
      math::Vec3(0.0f, -0.5f, 0.0f),
    };
    // clang-format on

    GLuint triangleVBO = 0;
    glGenBuffers(1, &triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(points.size() * sizeof(math::Vec3)),
                 points.data(), GL_STATIC_DRAW);

    GLuint triangleVBO2 = 0;
    glGenBuffers(1, &triangleVBO2);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO2);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(points2.size() * sizeof(math::Vec3)),
                 points2.data(), GL_STATIC_DRAW);

    triangleVAO = 0;
    glGenVertexArrays(1, &triangleVAO);
    glBindVertexArray(triangleVAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    triangleVAO2 = 0;
    glGenVertexArrays(1, &triangleVAO2);
    glBindVertexArray(triangleVAO2);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    const char* vertexShader = "#version 410 core\n"
                               "in vec3 vp;"
                               "void main() {"
                               "  gl_Position = vec4( vp, 1.0 );"
                               "}";

    const char* fragmentShader = "#version 410 core\n"
                                 "out vec4 frag_colour;"
                                 "void main() {"
                                 "  frag_colour = vec4( 0.5, 0.0, 0.5, 1.0 );"
                                 "}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);
    if (!checkShaderCompilation(vs, "Vertex")) {
        glDeleteShader(vs);
        return;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);
    if (!checkShaderCompilation(fs, "Fragment")) {
        glDeleteShader(fs);
        glDeleteShader(vs);
        return;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fs);
    glAttachShader(shaderProgram, vs);
    glLinkProgram(shaderProgram);

    glDeleteShader(fs);
    glDeleteShader(vs);

    if (!checkProgramLink(shaderProgram)) {
        glDeleteProgram(shaderProgram);
        shaderProgram = 0;
    }
}

void drawTriangle() {
    glUseProgram(shaderProgram);
    glBindVertexArray(triangleVAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(triangleVAO2);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

double getTime() {
    return static_cast<double>(SDL_GetTicks()) / 1000.0f;
}

double prevTick;
double fpsCooldown = 0.1f;
void fpsCounter(SDL_Window* window) {
    double currentTick = getTime();

    double elapsedTick = currentTick - prevTick;
    prevTick = currentTick;

    fpsCooldown -= elapsedTick;
    if (fpsCooldown < 0.0f && elapsedTick > 0.0f) {
        double fps = 1.0f / elapsedTick;

        SDL_SetWindowTitle(window, fmt::format("FPS: {}", fps).c_str());
        fpsCooldown = 0.1f;
    }
}

void Application::Init() {
    createWindow();
    createOpenGLContext();

    setupDrawTriangle();

    prevTick = getTime();
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        int width = 0;
        int height = 0;
        SDL_GetWindowSizeInPixels(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.075f, 0.075F, 0.11F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        drawTriangle();

        fpsCounter(window);

        SDL_GL_SwapWindow(window);
    }
}

void Application::createWindow() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fmt::println("Failed to initialize video: {}", SDL_GetError());
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    int context_flags = 0;
#ifdef __APPLE__
    context_flags |= SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;
#endif
#ifndef NDEBUG
    context_flags |= SDL_GL_CONTEXT_DEBUG_FLAG;
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, context_flags);

    window =
        SDL_CreateWindow("jiel", WINDOW_SIZE.Width, WINDOW_SIZE.Height,
                         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (window == nullptr) {
        fmt::println("Could not create a window: {}", SDL_GetError());
        SDL_Quit();
        return;
    }
}

void Application::createOpenGLContext() {
    context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        fmt::println("Could not create an OpenGL context: {}", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    if (gladLoadGL(SDL_GL_GetProcAddress) == 0) {
        fmt::println("Could not load OpenGL: {}", SDL_GetError());
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    SDL_GL_SetSwapInterval(1);
    fmt::print("OpenGL {}\n", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

Application::~Application() {
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
