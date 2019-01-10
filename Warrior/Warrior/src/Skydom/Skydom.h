#ifndef WARRIOR_SKYDOM_SKYDOM_H
#define WARRIOR_SKYDOM_SKYDOM_H

#include "Engine/Resources/Resources.h"
#include "Engine/Graphics/OpenGL/Program.h"
#include "Engine/Graphics/OpenGL/CubeMap.h"
#include "Engine/Graphics/OpenGL/VertexArray.h"
#include "Engine/Graphics/OpenGL/VertexBuffer.h"

namespace Warrior::Skydom
{
class Skydom
{
    using Program = WarriorEngine::Resources::Resource<WarriorEngine::Graphics::OpenGL::Program>;
    using CubeMap = WarriorEngine::Resources::Resource<WarriorEngine::Graphics::OpenGL::CubeMap>;
    using VertexArray = WarriorEngine::Graphics::OpenGL::VertexArray;
    using VertexBuffer = WarriorEngine::Graphics::OpenGL::VertexBuffer;

    Program program_;
    CubeMap cubeMap_;

    std::unique_ptr<VertexArray> vao_;
    std::unique_ptr<VertexBuffer> vbo_;

public:
    explicit Skydom(Program program, CubeMap cubeMap);
    void draw(const glm::mat4& projection, const glm::mat4& view) const;
};
}  // namespace Warrior::Skydom

#endif
