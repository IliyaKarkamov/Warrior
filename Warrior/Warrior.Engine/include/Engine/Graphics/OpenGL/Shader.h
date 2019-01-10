#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_SHADER_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_SHADER_H

#include "Engine/EngineAPI.h"
#include "Engine/Graphics/OpenGL/enums/ShaderType.h"
#include <string>

#define GLSL(version, source) "#version " #version "\n" #source

namespace WarriorEngine::Graphics::OpenGL
{
class WE_API Shader
{
    unsigned int id_;

public:
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    Shader(const ShaderType type) noexcept;
    Shader(const ShaderType type, const std::string& source) noexcept;

    ~Shader() noexcept;

    void setSource(const std::string& source) const noexcept;
    void compile() const noexcept;

    explicit operator unsigned int() const noexcept;

    std::string getInfoLog() const noexcept;

private:
    void destroy() const noexcept;
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
