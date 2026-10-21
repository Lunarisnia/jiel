#include "graphics/shader.hpp"

#include <glad/gl.h>

#include <string>
#include <utility>

Shader::Shader() : program(glCreateProgram()) {}

Shader::~Shader() {
    for (const auto stage : shaders) {
        glDeleteShader(stage);
    }
    if (program != 0) {
        glDeleteProgram(program);
    }
}

Shader::Shader(Shader&& other) noexcept
    : program(std::exchange(other.program, 0)), shaders(std::move(other.shaders)) {
    other.shaders.clear();
}

Shader& Shader::operator=(Shader&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    for (const auto stage : shaders) {
        glDeleteShader(stage);
    }
    if (program != 0) {
        glDeleteProgram(program);
    }
    program = std::exchange(other.program, 0);
    shaders = std::move(other.shaders);
    other.shaders.clear();
    return *this;
}

std::expected<void, std::string> Shader::Add(const std::string& source,
                                             unsigned int shaderType) {
    const GLuint stage = glCreateShader(shaderType);
    if (stage == 0) {
        return std::unexpected("Could not create shader stage");
    }
    const char* data = source.c_str();
    glShaderSource(stage, 1, &data, nullptr);
    glCompileShader(stage);

    GLint compiled = GL_FALSE;
    glGetShaderiv(stage, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE) {
        GLint logLength = 0;
        glGetShaderiv(stage, GL_INFO_LOG_LENGTH, &logLength);
        std::string log(static_cast<std::size_t>(logLength), '\0');
        GLsizei written = 0;
        glGetShaderInfoLog(stage, logLength, &written, log.data());
        log.resize(static_cast<std::size_t>(written));
        glDeleteShader(stage);
        return std::unexpected("Shader stage compilation failed:\n" + log);
    }

    shaders.push_back(stage);
    return {};
}

std::expected<void, std::string> Shader::Compile() {
    if (shaders.empty()) {
        return std::unexpected("No shader stages to link");
    }
    if (program == 0) {
        return std::unexpected("Could not create shader program");
    }
    for (const auto stage : shaders) {
        glAttachShader(program, stage);
    }
    glLinkProgram(program);
    for (const auto stage : shaders) {
        glDetachShader(program, stage);
        glDeleteShader(stage);
    }
    shaders.clear();

    GLint linked = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked == GL_TRUE) {
        return {};
    }

    GLint logLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::string log(static_cast<std::size_t>(logLength), '\0');
    GLsizei written = 0;
    glGetProgramInfoLog(program, logLength, &written, log.data());
    log.resize(static_cast<std::size_t>(written));
    return std::unexpected("Shader program link failed:\n" + log);
}

void Shader::Use() const {
    glUseProgram(program);
}

void Shader::SetFloatUniform(const std::string& name, float value) const {
    const GLint location = glGetUniformLocation(program, name.c_str());
    if (location != -1) {
        glProgramUniform1f(program, location, value);
    }
}

void Shader::SetMat4Uniform(const std::string& name, const math::Mat4& value) const {
    const GLint location = glGetUniformLocation(program, name.c_str());
    if (location != -1) {
        glProgramUniformMatrix4fv(program, location, 1, GL_TRUE, value.Data());
    }
}

void Shader::SetVec3Uniform(const std::string& name, const math::Vec3& value) const {
    const GLint location = glGetUniformLocation(program, name.c_str());
    if (location != -1) {
        glProgramUniform3f(program, location, value.x, value.y, value.z);
    }
}
