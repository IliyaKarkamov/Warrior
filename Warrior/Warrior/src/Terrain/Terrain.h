#ifndef WARRIOR_TERRAIN_TERRAIN_H
#define WARRIOR_TERRAIN_TERRAIN_H

#include "Engine/Graphics/Model.h"
#include "Engine/Graphics/Light.h"

namespace Warrior::Terrain
{
class Terrain
{
    using Texture = WarriorEngine::Resources::Resource<WarriorEngine::Graphics::OpenGL::Texture>;
    using Program = WarriorEngine::Resources::Resource<WarriorEngine::Graphics::OpenGL::Program>;
    using Model = std::unique_ptr<WarriorEngine::Graphics::Model>;

    Program program_;
    Model model_;
    Texture heightMap_;

    int size_;
    int maxheight_;
    int vertexCount_;
    glm::mat4 modelMatrix_;

public:
    explicit Terrain(Program program,
                     std::vector<std::pair<Texture, std::string>> diffuseTextures,
                     Texture height,
                     const int size,
                     const int maxheight,
                     const int vertexCount,
                     const glm::mat4& modelMatrix);

    void generate(std::vector<std::pair<Texture, std::string>> diffuseTextures);
    void loadLight(const WarriorEngine::Graphics::Light& light) const;

    void draw(const glm::mat4& viewMatrix,
              const glm::mat4& projectionMatrix,
              const glm::vec3& cameraPosition) const;
};
}  // namespace Warrior::Terrain

#endif
