#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_VERTEXBUFFER_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_VERTEXBUFFER_H

#include "Engine/EngineAPI.h"
#include "Engine/Graphics/OpenGL/enums/BufferUsage.h"

namespace WarriorEngine::Graphics::OpenGL
{
class WE_API VertexBuffer
{
    unsigned int id_;

public:
    VertexBuffer(const void* data, const int size, const BufferUsage usage) noexcept;
    ~VertexBuffer() noexcept;

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    VertexBuffer(VertexBuffer&& other) noexcept;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    void bind() const noexcept;
    void unbind() const noexcept;

private:
    void destroy() const noexcept;
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
