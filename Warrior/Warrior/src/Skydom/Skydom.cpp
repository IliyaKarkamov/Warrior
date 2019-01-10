#include "Skydom/Skydom.h"
#include "Engine/Graphics/OpenGL/enums/BufferUsage.h"
#include "Engine/Graphics/OpenGL/Renderer.h"
#include "Engine/Graphics/OpenGL/VertexBufferLayout.h"

namespace Warrior::Skydom
{
constexpr float c_skydomVertices[] = 
{      
    -1.f,  1.f, -1.f,
    -1.f, -1.f, -1.f,
     1.f, -1.f, -1.f,
     1.f, -1.f, -1.f,
     1.f,  1.f, -1.f,
    -1.f,  1.f, -1.f,

    -1.f, -1.f,  1.f,
    -1.f, -1.f, -1.f,
    -1.f,  1.f, -1.f,
    -1.f,  1.f, -1.f,
    -1.f,  1.f,  1.f,
    -1.f, -1.f,  1.f,

     1.f, -1.f, -1.f,
     1.f, -1.f,  1.f,
     1.f,  1.f,  1.f,
     1.f,  1.f,  1.f,
     1.f,  1.f, -1.f,
     1.f, -1.f, -1.f,

    -1.f, -1.f,  1.f,
    -1.f,  1.f,  1.f,
     1.f,  1.f,  1.f,
     1.f,  1.f,  1.f,
     1.f, -1.f,  1.f,
    -1.f, -1.f,  1.f,

    -1.f,  1.f, -1.f,
     1.f,  1.f, -1.f,
     1.f,  1.f,  1.f,
     1.f,  1.f,  1.f,
    -1.f,  1.f,  1.f,
    -1.f,  1.f, -1.f,

    -1.f, -1.f, -1.f,
    -1.f, -1.f,  1.f,
     1.f, -1.f, -1.f,
     1.f, -1.f, -1.f,
    -1.f, -1.f,  1.f,
     1.f, -1.f,  1.f
};


Skydom::Skydom(Program program, CubeMap cubeMap) : program_(std::move(program)), cubeMap_(std::move(cubeMap))
{
    vao_ = std::make_unique<VertexArray>();
    vao_->bind();

    vbo_ = std::make_unique<VertexBuffer>(c_skydomVertices, sizeof(c_skydomVertices),
                                      WarriorEngine::Graphics::OpenGL::BufferUsage::StaticDraw);

    WarriorEngine::Graphics::OpenGL::VertexBufferLayout vbl;
    vbl.push<float>(3);

    vao_->addBuffer(*vbo_, vbl);
}

void Skydom::draw(const glm::mat4& projection, const glm::mat4& view) const
{
    using WarriorEngine::Graphics::OpenGL::Renderer;
    using WarriorEngine::Graphics::OpenGL::PrimitiveType;

    auto viewMatrix = view;
    viewMatrix[3][0] = 0.f;
    viewMatrix[3][1] = 0.f;
    viewMatrix[3][2] = 0.f;

    program_->bind();
    program_->setUniform("u_Skydom", 0);
    program_->setUniform("u_Projection", projection);
    program_->setUniform("u_View", viewMatrix);
    cubeMap_->bind(0);

    vao_->bind();
    Renderer::drawArrays(PrimitiveType::Triangles, 0, 36);
}
}  // namespace Warrior::Skydom
