#include "mesh_loader.hpp"
#include "file.hpp"
#include "graphics/mesh.hpp"

std::expected<Mesh, std::string> MeshLoader::LoadOBJ(const std::string& path) {
    auto loaded = File::LoadOBJ(path);
    if (!loaded) {
        return std::unexpected(loaded.error());
    }

    MeshData data{};
    for (unsigned int meshIndex = 0; meshIndex < (*loaded)->mNumMeshes; ++meshIndex) {
        const aiMesh& mesh = *(*loaded)->mMeshes[meshIndex];
        const auto vertexOffset = static_cast<GLuint>(data.vertice.size());

        for (unsigned int vertexIndex = 0; vertexIndex < mesh.mNumVertices; ++vertexIndex) {
            const aiVector3D& vertex = mesh.mVertices[vertexIndex];
            data.vertice.emplace_back(vertex.x, vertex.y, vertex.z);
        }

        for (unsigned int faceIndex = 0; faceIndex < mesh.mNumFaces; ++faceIndex) {
            const aiFace& face = mesh.mFaces[faceIndex];
            for (unsigned int index = 0; index < face.mNumIndices; ++index) {
                data.indice.emplace_back(vertexOffset + face.mIndices[index]);
            }
        }
    }

    return Mesh{data};
}
