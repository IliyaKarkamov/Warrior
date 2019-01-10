#ifndef WARRIOR_ENGINE_GRAPHICS_MODEL_H
#define WARRIOR_ENGINE_GRAPHICS_MODEL_H

#include "Engine/EngineAPI.h"
#include "Engine/Graphics/Mesh.h"
#include <vector>

namespace WarriorEngine::Graphics
{
class WE_API Model
{
    std::vector<std::shared_ptr<Mesh>> meshes_;

public:
    void addMesh(const std::shared_ptr<Mesh>& mesh);
    void draw(const Resources::Resource<OpenGL::Program>& program);
};
}  // namespace WarriorEngine::Graphics

#endif
