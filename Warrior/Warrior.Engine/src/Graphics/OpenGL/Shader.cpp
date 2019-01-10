#include "Engine/Graphics/OpenGL/Shader.h"
#include "Engine/Core.h"
#include "Utils/ErrorHandler.h"
#include <GL/glew.h>

namespace WarriorEngine::Graphics::OpenGL
{
Shader::Shader(Shader&& other) noexcept
{
    id_ = other.id_;
    other.id_ = 0u;
}

Shader& Shader::operator=(Shader&& other) noexcept
{
    if (id_ != other.id_)
    {
        destroy();
        id_ = other.id_;
    }

    return *this;
}

Shader::Shader(const ShaderType type) noexcept : id_(0u)
{
    GL_CALL(id_ = glCreateShader(static_cast<unsigned int>(type)));
}

Shader::Shader(const ShaderType type, const std::string& source) noexcept : id_(0u)
{
    GL_CALL(id_ = glCreateShader(static_cast<unsigned int>(type)));
    setSource(source);
}

Shader::~Shader() noexcept { destroy(); }

void Shader::setSource(const std::string& source) const noexcept
{
    const auto sourceCode = source.data();
    GL_CALL(glShaderSource(id_, 1, &sourceCode, nullptr));
}

void Shader::compile() const noexcept
{
    GLint status;

    GL_CALL(glCompileShader(id_));
    GL_CALL(glGetShaderiv(id_, GL_COMPILE_STATUS, &status));

    if (status == GL_FALSE)
        WE_ENGINE_ERROR("[OpenGL error]: Shader compilation failed: %s", getInfoLog().c_str());
}

Shader::operator unsigned int() const noexcept { return id_; }

std::string Shader::getInfoLog() const noexcept
{
    GLint logLength;
    GL_CALL(glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &logLength));

    if (logLength > 0)
    {
        std::string infoLog(logLength, 0);
        GL_CALL(glGetShaderInfoLog(id_, logLength, &logLength, &infoLog[0]));

        return infoLog;
    }

    return "";
}

void Shader::destroy() const noexcept
{
    if (id_ == 0u)
        return;

    GL_CALL(glDeleteShader(id_));
}
}  // namespace WarriorEngine::Graphics::OpenGL