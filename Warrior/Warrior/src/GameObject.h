#ifndef WARRIOR_GAME_OBJECT_H
#define WARRIOR_GAME_OBJECT_H

#include "Engine/Graphics/Model.h"
#include "Engine/Graphics/Light.h"

class GameObject
{
    using Program = WarriorEngine::Resources::Resource<WarriorEngine::Graphics::OpenGL::Program>;
    using Model = WarriorEngine::Resources::Resource<WarriorEngine::Graphics::Model>;

    Program program_;
    Model model_;
    glm::mat4 modelMatrix_;

public:
    GameObject(Program program, Model model, const glm::mat4& modelMatrix);

    void setModelMatrix(const glm::mat4& modelMatrix);

    void draw(const glm::mat4& viewMatrix,
              const glm::mat4& projMatrix,
              const WarriorEngine::Graphics::Light& light,
              const glm::vec3& cameraPosition) const;
};

#endif