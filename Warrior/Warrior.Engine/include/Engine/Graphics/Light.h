#ifndef WARRIOR_ENGINE_GRAPHICS_LIGHT_H
#define WARRIOR_ENGINE_GRAPHICS_LIGHT_H

#include "Engine/EngineAPI.h"
#include "OpenGL/glm/vec3.hpp"

namespace WarriorEngine::Graphics
{
class WE_API Light
{
    glm::vec3 position_;
    glm::vec3 color_;

public:
    explicit Light(const glm::vec3& position, const glm::vec3& color);

    glm::vec3 getPosition() const noexcept;
    glm::vec3 getColor() const noexcept;

    void setPosition(const glm::vec3& position);
    void setColor(const glm::vec3& color);
};
}  // namespace WarriorEngine::Graphics

#endif
