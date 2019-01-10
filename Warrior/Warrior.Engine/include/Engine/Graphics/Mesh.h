#ifndef WARRIOR_ENGINE_GRAPHICS_MESH_H
#define WARRIOR_ENGINE_GRAPHICS_MESH_H

#include "Engine/EngineAPI.h"
#include "Engine/Resources/Resources.h"
#include "Engine/Graphics/OpenGL/Program.h"
#include "Engine/Graphics/OpenGL/VertexArray.h"
#include "Engine/Graphics/OpenGL/VertexBuffer.h"
#include "Engine/Graphics/OpenGL/IndexBuffer.h"
#include "Engine/Graphics/OpenGL/Texture.h"
#include "Engine/Graphics/OpenGL/glm/vec3.hpp"
#include "Engine/Graphics/OpenGL/glm/vec2.hpp"
#include <memory>
#include <vector>

namespace WarriorEngine::Graphics
{
struct WE_API Vertex
{
    glm::vec3 position{};
    glm::vec3 normal{};
    glm::vec2 texCoords{};
    glm::vec3 tangent{};
    glm::vec3 bitangent{};
};

class WE_API Mesh
{
    std::unique_ptr<OpenGL::VertexArray> vao_ = nullptr;
    std::unique_ptr<OpenGL::VertexBuffer> vbo_ = nullptr;
    std::unique_ptr<OpenGL::IndexBuffer> ebo_ = nullptr;
    std::vector<std::pair<Resources::Resource<OpenGL::Texture>, std::string>> textures_;

public:
    Mesh(std::vector<Vertex> vertices,
         std::vector<unsigned int> indices,
         std::vector<std::pair<Resources::Resource<OpenGL::Texture>, std::string>> textures);

    void draw(const Resources::Resource<OpenGL::Program>& program);
};
}  // namespace WarriorEngine::Graphics

#endif
