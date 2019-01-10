#include "GameObject.h"
#include <Engine/Graphics/OpenGL/Renderer.h>

GameObject::GameObject(Program program, Model model, const glm::mat4& modelMatrix)
    : program_(std::move(program)), model_(std::move(model)), modelMatrix_(modelMatrix)
{}

void GameObject::setModelMatrix(const glm::mat4& modelMatrix) { modelMatrix_ = modelMatrix; }

void GameObject::draw(const glm::mat4& viewMatrix,
                      const glm::mat4& projMatrix,
                      const WarriorEngine::Graphics::Light& light,
                      const glm::vec3& cameraPosition) const
{
    namespace GL = WarriorEngine::Graphics::OpenGL;

    GL::Renderer::disable(GL::Capability::CullFace);

    program_->bind();
    program_->setUniform("u_Model", modelMatrix_);
    program_->setUniform("u_View", viewMatrix);
    program_->setUniform("u_Projection", projMatrix);
    program_->setUniform("u_ViewPosition", cameraPosition);
    program_->setUniform("u_Light.position", light.getPosition());
    program_->setUniform("u_Light.color", light.getColor());
    program_->setUniform("u_Light.ambientIntensity", glm::vec3(0.2f, 0.2f, 0.2f));
    program_->setUniform("u_Light.diffuseIntensity", glm::vec3(0.8f, 0.8f, 0.8f));
    program_->setUniform("u_Light.specularIntensity", glm::vec3(1.f, 1.f, 1.f));
    program_->setUniform("u_SkyColor", glm::vec3(0.5f, 0.5f, 0.5f));

    model_->draw(program_);
    GL::Renderer::enable(GL::Capability::CullFace);
}
