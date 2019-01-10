#ifndef WARRIOR_ENGINE_GRAPHICS_CAMERA_H
#define WARRIOR_ENGINE_GRAPHICS_CAMERA_H

#include "Engine/EngineAPI.h"
#include "OpenGL/glm/vec3.hpp"
#include "OpenGL/glm/mat4x2.hpp"

constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float ZOOM = 45.0f;

namespace WarriorEngine::Graphics
{
enum class MoveDirection
{
    Left,
    Right,
    Forward,
    Backward
};

class WE_API Camera
{
    glm::vec3 position_{};
    glm::vec3 front_;
    glm::vec3 up_{};
    glm::vec3 right_{};
    glm::vec3 worldUp_{};

    float yaw_;
    float pitch_;
    float zoom_;

    bool trailingDirection_;

public:
    explicit Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.3f),
                    const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
                    const float yaw = YAW,
                    const float pitch = PITCH,
                    const float zoom = ZOOM,
                    const bool trailingDirection = false);

    void move(const MoveDirection direction, const float amount);

    void updateYaw(const float dYaw);
    void updatePitch(const float dPitch);
    void updateZoom(const float dZoom);

    glm::mat4 getViewMatrix() const noexcept;
    float getZoom() const noexcept { return zoom_; }
    glm::vec3 getPosition() const noexcept { return position_; };

private:
    void updateCameraVectors();
};
}  // namespace WarriorEngine::Graphics

#endif
