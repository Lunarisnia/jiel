#include "graphics/shader.hpp"
#include "fmt/base.h"
#include "glad/gl.h"

Shader::Shader() {
    program = glCreateProgram();
}

void Shader::Add(std::string source, GLint shaderType) {
    GLuint shader = glCreateShader(shaderType);
    const char* shaderSource = source.c_str();
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    if (!checkShaderCompilation(shader, shaderType)) {
        glDeleteShader(shader);
        return;
    }

    shaders.emplace_back(shader);
}

void Shader::Compile() {
    for (const GLuint& s : shaders) {
        glAttachShader(program, s);
    }
    glLinkProgram(program);

    for (const GLuint& s : shaders) {
        glDeleteShader(s);
    }

    if (!checkProgramLink(program)) {
        glDeleteProgram(program);
    }
}

void Shader::Use() {
    glUseProgram(program);
}

bool Shader::checkShaderCompilation(GLuint shader, GLint shaderType) {
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

    std::string shaderName = "";
    if (shaderType == GL_FRAGMENT_SHADER) {
        shaderName = "Fragment";
    } else {
        shaderName = "Vertex";
    }

    fmt::println(stderr, "{} shader compilation failed:\n{}", shaderName, log);
    return false;
}

bool Shader::checkProgramLink(GLuint program) {
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
