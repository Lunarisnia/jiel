#include "file.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
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

std::expected<std::unique_ptr<aiScene>, std::string>
File::LoadOBJ(const std::filesystem::path& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.string(), aiProcess_Triangulate);
    if (scene == nullptr) {
        return std::unexpected(importer.GetErrorString());
    }

    return std::unique_ptr<aiScene>{importer.GetOrphanedScene()};
}
