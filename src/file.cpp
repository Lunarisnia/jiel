#include "file.hpp"

#include <fstream>
#include <iterator>
#include <stdexcept>

std::string File::LoadFile(const std::filesystem::path& path)
{
    std::ifstream stream(path, std::ios::binary);
    if (!stream) {
        throw std::runtime_error("Could not open file: " + path.string());
    }

    std::string contents{std::istreambuf_iterator<char>{stream},
                         std::istreambuf_iterator<char>{}};
    if (stream.bad()) {
        throw std::runtime_error("Could not read file: " + path.string());
    }

    return contents;
}
