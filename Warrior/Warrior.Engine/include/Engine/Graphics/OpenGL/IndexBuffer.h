#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_INDEXBUFFER_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_INDEXBUFFER_H

#include "Engine/EngineAPI.h"
#include "Engine/Graphics/OpenGL/enums/BufferUsage.h"

namespace WarriorEngine::Graphics::OpenGL
{
class WE_API IndexBuffer
{
    unsigned int id_;
    int count_;

public:
    IndexBuffer(const unsigned int* indices, const int count, const BufferUsage usage) noexcept;
    ~IndexBuffer() noexcept;

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    IndexBuffer(IndexBuffer&& other) noexcept;
    IndexBuffer& operator=(IndexBuffer&& other) noexcept;

    void bind() const noexcept;
    void unbind() const noexcept;

    int getCount() const noexcept { return count_; }

private:
    void destroy() const noexcept;
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
