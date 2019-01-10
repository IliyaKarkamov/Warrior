#include "Engine/Graphics/Mesh.h"
#include "Engine/Graphics/OpenGL/VertexBufferLayout.h"
#include "Engine/Graphics/OpenGL/Renderer.h"

namespace WarriorEngine::Graphics
{
Mesh::Mesh(std::vector<Vertex> vertices,
           std::vector<unsigned> indices,
           std::vector<std::pair<Resources::Resource<OpenGL::Texture>, std::string>> textures)
    : textures_(std::move(textures))
{
    vao_ = std::make_unique<OpenGL::VertexArray>();
    vao_->bind();

    vbo_ = std::make_unique<OpenGL::VertexBuffer>(&vertices[0], vertices.size() * sizeof(Vertex),
                                                  OpenGL::BufferUsage::DynamicDraw);

    OpenGL::VertexBufferLayout vbl;
    vbl.push<float>(3);
    vbl.push<float>(3);
    vbl.push<float>(2);
    vbl.push<float>(3);
    vbl.push<float>(3);

    vao_->addBuffer(*vbo_, vbl);

    ebo_ =
        std::make_unique<OpenGL::IndexBuffer>(&indices[0], indices.size(), OpenGL::BufferUsage::DynamicDraw);

    vao_->unbind();
}

void Mesh::draw(const Resources::Resource<OpenGL::Program>& program)
{
    program->bind();

    auto diffuseNum = 1u;
    auto specularNum = 1u;
    auto normalNum = 1u;
    auto heightNum = 1u;

    for (auto i = 0u; i < textures_.size(); ++i)
    {
        auto&& [texture, type] = textures_[i];

        std::string number;

        if (type == "texture_diffuse")
            number = std::to_string(diffuseNum++);
        else if (type == "texture_specular")
            number = std::to_string(specularNum++);
        else if (type == "texture_normal")
            number = std::to_string(normalNum++);
        else if (type == "texture_height")
            number = std::to_string(heightNum++);

        texture->bind(i);
        program->setUniform(type + number, static_cast<int>(i));
    }

    vao_->bind();

    OpenGL::Renderer::drawElements(OpenGL::PrimitiveType::Triangles, 0, ebo_->getCount(),
                                   OpenGL::DataType::UnsignedInt);
}
}  // namespace WarriorEngine::Graphics
