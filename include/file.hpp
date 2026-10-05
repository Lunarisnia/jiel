#pragma once

#include <filesystem>
#include <string>

class File {
  public:
    File() = delete;

    [[nodiscard]] static std::string LoadFile(const std::filesystem::path& path);
};
