#include "Engine/Graphics/OpenGL/Program.h"
#include "Engine/Graphics/OpenGL/Shader.h"
#include "Utils/ErrorHandler.h"
#include "Engine/Core.h"
#include <GL/glew.h>

namespace WarriorEngine::Graphics::OpenGL
{
Program::Program() noexcept { GL_CALL(id_ = glCreateProgram()); }

Program::Program(const Shader& vertex, const Shader& fragment) noexcept
{
    GL_CALL(id_ = glCreateProgram());

    attach(vertex);
    attach(fragment);

    link();
}

Program::~Program() noexcept { destroy(); }

Program::Program(Program&& other) noexcept
{
    id_ = other.id_;
    other.id_ = 0u;
}

Program& Program::operator=(Program&& other) noexcept
{
    if (id_ != other.id_)
    {
        destroy();
        id_ = other.id_;
        other.id_ = 0u;
    }

    return *this;
}

void Program::destroy() const noexcept
{
    if (id_ == 0u)
        return;

    GL_CALL(glDeleteProgram(id_));
}

void Program::attach(const Shader& shader) const noexcept
{
    GL_CALL(glAttachShader(id_, static_cast<unsigned int>(shader)));
}

void Program::link() const noexcept
{
    GLint linkStatus;

    glLinkProgram(id_);
    glGetProgramiv(id_, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == GL_FALSE)
        WE_ENGINE_ERROR("[OpenGL error]: Program linking failed: %s", getInfoLog().c_str());
}

void Program::bind() const noexcept { GL_CALL(glUseProgram(id_)); }

void Program::unbind() const noexcept { GL_CALL(glUseProgram(0u)); }

int Program::getAttributeLocation(const std::string& name) const noexcept
{
    GL_CALL(const auto location = glGetAttribLocation(id_, name.c_str()));
    return location;
}

int Program::getUniformLocation(const std::string& name) const noexcept
{
    if (const auto it = uniformLocationCache_.find(name); it != uniformLocationCache_.end())
        return it->second;

    GL_CALL(const auto location = glGetUniformLocation(id_, name.c_str()));
    uniformLocationCache_[name] = location;
    return location;
}

void Program::setUniform(const std::string& name, const int value) const noexcept
{
    GL_CALL(glUniform1i(getUniformLocation(name), value));
}

void Program::setUniform(const std::string& name, const float value) const noexcept
{
    GL_CALL(glUniform1f(getUniformLocation(name), value));
}

void Program::setUniform(const std::string& name, const glm::vec2& value) const noexcept
{
    GL_CALL(glUniform2f(getUniformLocation(name), value.x, value.y));
}

void Program::setUniform(const std::string& name, const glm::vec3& value) const noexcept
{
    GL_CALL(glUniform3f(getUniformLocation(name), value.x, value.y, value.z));
}

void Program::setUniform(const std::string& name, const glm::vec4& value) const noexcept
{
    GL_CALL(glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w));
}

void Program::setUniform(const std::string& name, const glm::mat3& value) const noexcept
{
    GL_CALL(glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]));
}

void Program::setUniform(const std::string& name, const glm::mat4& value) const noexcept
{
    GL_CALL(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]));
}

std::string Program::getInfoLog() const noexcept
{
    GLint logLength;
    GL_CALL(glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &logLength));

    if (logLength > 0)
    {
        std::string infoLog(logLength, 0);
        GL_CALL(glGetProgramInfoLog(id_, logLength, &logLength, &infoLog[0]));

        return infoLog;
    }

    return "";
}
}  // namespace WarriorEngine::Graphics::OpenGL
