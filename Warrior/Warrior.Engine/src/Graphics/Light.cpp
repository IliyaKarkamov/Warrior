#include "Engine/Graphics/Light.h"

namespace WarriorEngine::Graphics
{
Light::Light(const glm::vec3& position, const glm::vec3& color) : position_(position), color_(color) {}

glm::vec3 Light::getPosition() const noexcept { return position_; }

glm::vec3 Light::getColor() const noexcept { return color_; }

void Light::setPosition(const glm::vec3& position) { position_ = position; }

void Light::setColor(const glm::vec3& color) { color_ = color; }
}  // namespace WarriorEngine::Graphics
