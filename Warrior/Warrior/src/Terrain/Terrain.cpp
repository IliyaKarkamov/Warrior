#include "Terrain.h"
#include "Engine/Graphics/Mesh.h"

namespace Warrior::Terrain
{
constexpr auto c_maxPixelColor = 256 * 256 * 256;

Terrain::Terrain(Program program,
                 std::vector<std::pair<Texture, std::string>> diffuseTextures,
                 Texture height,
                 const int size,
                 const int maxheight,
                 const int vertexCount,
                 const glm::mat4& modelMatrix)
    : program_(std::move(program)),
      heightMap_(std::move(height)),
      size_(size),
      maxheight_(maxheight),
      vertexCount_(vertexCount),
      modelMatrix_(modelMatrix)
{
    generate(std::move(diffuseTextures));
}

void Terrain::generate(std::vector<std::pair<Texture, std::string>> diffuseTextures)
{
    std::vector<WarriorEngine::Graphics::Vertex> vertices;
    vertices.reserve(vertexCount_ * vertexCount_);

    for (auto i = 0; i < vertexCount_; ++i)
    {
        for (auto j = 0; j < vertexCount_; ++j)
        {
            vertices.emplace_back();
            auto& vertex = vertices.back();

            float h = heightMap_->getRgbValue(i, j);
            h /= c_maxPixelColor;
            h *= maxheight_;

            vertex.position.x = static_cast<float>(j) / (vertexCount_ - 1) * size_;
            vertex.position.y = h;
            vertex.position.z = static_cast<float>(i) / (vertexCount_ - 1) * size_;

            vertex.normal.x = 0.f;
            vertex.normal.y = 1.f;
            vertex.normal.z = 0.f;

            vertex.texCoords.x = static_cast<float>(j) / (vertexCount_ - 1);
            vertex.texCoords.y = static_cast<float>(i) / (vertexCount_ - 1);
        }
    }

    std::vector<unsigned int> indices;
    indices.reserve(6 * (vertexCount_ - 1) * (vertexCount_ - 1));

    for (auto gz = 0; gz < vertexCount_ - 1; ++gz)
    {
        for (auto gx = 0; gx < vertexCount_ - 1; ++gx)
        {
            const auto topLeft = gz * vertexCount_ + gx;
            const auto topRight = topLeft + 1;
            const auto bottomLeft = (gz + 1) * vertexCount_ + gx;
            const auto bottomRight = bottomLeft + 1;

            indices.emplace_back(topLeft);
            indices.emplace_back(bottomLeft);
            indices.emplace_back(topRight);
            indices.emplace_back(topRight);
            indices.emplace_back(bottomLeft);
            indices.emplace_back(bottomRight);
        }
    }

    auto mesh = std::make_unique<WarriorEngine::Graphics::Mesh>(std::move(vertices), std::move(indices),
                                                                std::move(diffuseTextures));

    model_ = std::make_unique<WarriorEngine::Graphics::Model>();
    model_->addMesh(std::move(mesh));
}

void Terrain::loadLight(const WarriorEngine::Graphics::Light& light) const
{
    program_->bind();
    program_->setUniform("u_Light.position", light.getPosition());
    program_->setUniform("u_Light.color", light.getColor());
    program_->setUniform("u_Light.ambientIntensity", glm::vec3(0.01f, 0.01f, 0.01f));
    program_->setUniform("u_Light.diffuseIntensity", glm::vec3(0.8f, 0.8f, 0.8f));
    program_->setUniform("u_Light.specularIntensity", glm::vec3(1.f, 1.f, 1.f));
    program_->setUniform("u_SkyColor", glm::vec3(0.5f, 0.5f, 0.5f));
}

void Terrain::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition) const
{
    const auto mvp = projectionMatrix * viewMatrix * modelMatrix_;

    program_->bind();
    program_->setUniform("u_Projection", projectionMatrix);
    program_->setUniform("u_View", viewMatrix);
    program_->setUniform("u_Model", modelMatrix_);
    program_->setUniform("u_ViewPosition", cameraPosition);

    model_->draw(program_);
}

}  // namespace Warrior::Terrain
