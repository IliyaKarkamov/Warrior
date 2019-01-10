#include "Engine/Graphics/Camera.h"
#include <Engine/Graphics/OpenGL/glm/ext/matrix_transform.inl>
#include <Engine/Graphics/OpenGL/glm/detail/func_trigonometric.inl>

namespace WarriorEngine::Graphics
{
Camera::Camera(const glm::vec3& position,
               const glm::vec3& up,
               const float yaw,
               const float pitch,
               const float zoom,
               const bool trailingDirection)
    : position_(position),
      front_(glm::vec3(0.f, 0.f, -1.f)),
      worldUp_(up),
      yaw_(yaw),
      pitch_(pitch),
      zoom_(zoom),
      trailingDirection_(trailingDirection)
{
    updateCameraVectors();
}

void Camera::move(const MoveDirection direction, const float amount)
{
    if (direction == MoveDirection::Left)
        position_ -= right_ * amount;
    else if (direction == MoveDirection::Right)
        position_ += right_ * amount;
    else if (direction == MoveDirection::Forward)
        position_ += front_ * amount;
    else if (direction == MoveDirection::Backward)
        position_ -= front_ * amount;
}

void Camera::updateYaw(const float dYaw)
{
    if (trailingDirection_)
        yaw_ += dYaw;
    else
        yaw_ -= dYaw;

    updateCameraVectors();
}

void Camera::updatePitch(const float dPitch)
{
    if (trailingDirection_)
        pitch_ -= dPitch;
    else
        pitch_ += dPitch;

    if (pitch_ > 89.0f)
        pitch_ = 89.0f;

    if (pitch_ < -89.0f)
        pitch_ = -89.0f;

    updateCameraVectors();
}

void Camera::updateZoom(const float dZoom)
{
    if (zoom_ >= 1.0f && zoom_ <= 45.0f)
        zoom_ -= dZoom;

    if (zoom_ <= 1.0f)
        zoom_ = 1.0f;
    if (zoom_ >= 45.0f)
        zoom_ = 45.0f;
}

glm::mat4 Camera::getViewMatrix() const noexcept { return glm::lookAt(position_, position_ + front_, up_); }

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);

    right_ = glm::normalize(glm::cross(front_, worldUp_));
    up_ = glm::normalize(glm::cross(right_, front_));
}
}  // namespace WarriorEngine::Graphics
