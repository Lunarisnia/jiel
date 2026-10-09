#pragma once

#include <assimp/scene.h>
#include <expected>
#include <filesystem>
#include <memory>
#include <string>

class File {
  public:
    File() = delete;

    [[nodiscard]] static std::string LoadFile(const std::filesystem::path& path);
    [[nodiscard]] static std::expected<std::unique_ptr<aiScene>, std::string>
    LoadOBJ(const std::filesystem::path& path);
};
