#include "Engine/Graphics/OpenGL/Renderer.h"
#include "Utils/ErrorHandler.h"
#include "Engine/Core.h"
#include <GL/glew.h>

namespace WarriorEngine::Graphics::OpenGL
{
void Renderer::viewport(const int x, const int y, const int width, const int height)
{
    GL_CALL(glViewport(x, y, width, height));
}

void Renderer::wireframe(const bool isOn)
{
    if (isOn)
    {
        GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    }
    else
    {
        GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
    }
}

void Renderer::enable(const Capability capability)
{
    GL_CALL(glEnable(static_cast<unsigned int>(capability)));
}

void Renderer::disable(const Capability capability)
{
    GL_CALL(glDisable(static_cast<unsigned int>(capability)));
}

void Renderer::cullFace(const CullFaceMode mode) { GL_CALL(glCullFace(static_cast<unsigned int>(mode))); }

void Renderer::depthMask(const bool enable) { GL_CALL(glDepthMask(enable ? GL_TRUE : GL_FALSE)); }

void Renderer::depthFunc(const DepthFunc func)
{
    GL_CALL(glDepthFunc(static_cast<unsigned int>(func)));
}

void Renderer::blendFunc(const BlendingFactor sfactor, const BlendingFactor dfactor)
{
    GL_CALL(glBlendFunc(static_cast<unsigned int>(sfactor), static_cast<unsigned int>(dfactor)));
}

void Renderer::blendEquation(const BlendingEquation mode)
{
    GL_CALL(glBlendEquation(static_cast<unsigned int>(mode)));
}

void Renderer::clearColor(const glm::vec4& color)
{
    GL_CALL(glClearColor(color.r, color.g, color.b, color.a));
}

void Renderer::clear(const BufferType buffers) { GL_CALL(glClear(static_cast<unsigned int>(buffers))); }

void Renderer::drawArrays(const PrimitiveType mode, const int offset, const int vertices)
{
    GL_CALL(glDrawArrays(static_cast<unsigned int>(mode), offset, vertices));
}

void Renderer::drawElements(const PrimitiveType mode, const int offset, const int count, const DataType type)
{
    GL_CALL(glDrawElements(static_cast<unsigned int>(mode), count, static_cast<unsigned int>(type),
                           reinterpret_cast<const GLvoid*>(offset)));
}
}  // namespace WarriorEngine::Graphics::OpenGL
