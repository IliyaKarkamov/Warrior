#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_VERTEXARRAY_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_VERTEXARRAY_H

#include "Engine/EngineAPI.h"

namespace WarriorEngine::Graphics::OpenGL
{
class VertexBuffer;
class VertexBufferLayout;

class WE_API VertexArray
{
    unsigned int id_;

public:
    VertexArray() noexcept;
    ~VertexArray() noexcept;

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    VertexArray(VertexArray&& other) noexcept;
    VertexArray& operator=(VertexArray&& other) noexcept;

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const noexcept;

    void bind() const noexcept;
    void unbind() const noexcept;

private:
    void destroy() const noexcept;
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif