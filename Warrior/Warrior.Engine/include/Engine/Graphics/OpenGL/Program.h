#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_PROGRAM_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_PROGRAM_H

#include "Engine/EngineAPI.h"
#include "Engine/Graphics/OpenGL/glm/vec2.hpp"
#include "Engine/Graphics/OpenGL/glm/vec3.hpp"
#include "Engine/Graphics/OpenGL/glm/vec4.hpp"
#include "Engine/Graphics/OpenGL/glm/mat3x3.hpp"
#include "Engine/Graphics/OpenGL/glm/mat4x4.hpp"
#include <string>
#include <unordered_map>

namespace WarriorEngine::Graphics::OpenGL
{
class Shader;

class WE_API Program
{
    unsigned int id_;

    mutable std::unordered_map<std::string, int> uniformLocationCache_;

public:
    Program() noexcept;
    Program(const Shader& vertex, const Shader& fragment) noexcept;
    ~Program() noexcept;

    Program(const Program&) = delete;
    Program& operator=(const Program&) = delete;

    Program(Program&& other) noexcept;
    Program& operator=(Program&& other) noexcept;

    void attach(const Shader& shader) const noexcept;
    void link() const noexcept;

    void bind() const noexcept;
    void unbind() const noexcept;

    int getAttributeLocation(const std::string& name) const noexcept;
    int getUniformLocation(const std::string& name) const noexcept;

    void setUniform(const std::string& name, const int value) const noexcept;
    void setUniform(const std::string& name, const float value) const noexcept;
    void setUniform(const std::string& name, const glm::vec2& value) const noexcept;
    void setUniform(const std::string& name, const glm::vec3& value) const noexcept;
    void setUniform(const std::string& name, const glm::vec4& value) const noexcept;
    void setUniform(const std::string& name, const glm::mat3& value) const noexcept;
    void setUniform(const std::string& name, const glm::mat4& value) const noexcept;

    std::string getInfoLog() const noexcept;

private:
    void destroy() const noexcept;
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
