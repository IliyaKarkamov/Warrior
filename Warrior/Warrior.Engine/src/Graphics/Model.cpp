#include "Engine/Graphics/Model.h"

namespace WarriorEngine::Graphics
{
void Model::addMesh(const std::shared_ptr<Mesh>& mesh) { meshes_.push_back(mesh); }

void Model::draw(const Resources::Resource<OpenGL::Program>& program)
{
    for (auto& mesh : meshes_)
        mesh->draw(program);
}
}  // namespace WarriorEngine::Graphics
