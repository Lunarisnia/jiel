#pragma once

#include "math/mat4.hpp"
#include "math/vec3.hpp"

#include <expected>
#include <string>
#include <vector>

class Shader {
  public:
    Shader();
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    [[nodiscard]] std::expected<void, std::string> Add(const std::string& source,
                                                       unsigned int shaderType);
    [[nodiscard]] std::expected<void, std::string> Compile();

    void Use() const;
    void SetFloatUniform(const std::string& name, float value) const;
    void SetMat4Uniform(const std::string& name, const math::Mat4& value) const;
    void SetVec3Uniform(const std::string& name, const math::Vec3& value) const;

  private:
    unsigned int program = 0;
    std::vector<unsigned int> shaders{};
};
