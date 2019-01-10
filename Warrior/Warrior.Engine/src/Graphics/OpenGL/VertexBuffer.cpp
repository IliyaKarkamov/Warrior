#include "Engine/Graphics/OpenGL/VertexBuffer.h"
#include "Engine/Core.h"
#include "Utils/ErrorHandler.h"

namespace WarriorEngine::Graphics::OpenGL
{
VertexBuffer::VertexBuffer(const void* data, const int size, const BufferUsage usage) noexcept : id_(0u)
{
    GL_CALL(glGenBuffers(1, &id_));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, id_));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, static_cast<unsigned int>(usage)));
}

VertexBuffer::~VertexBuffer() noexcept { destroy(); }

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
{
    id_ = other.id_;
    other.id_ = 0u;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    if (id_ != other.id_)
    {
        destroy();
        id_ = other.id_;
    }

    return *this;
}

void VertexBuffer::destroy() const noexcept
{
    if (id_ == 0u)
        return;

    GL_CALL(glDeleteBuffers(1, &id_));
}

void VertexBuffer::bind() const noexcept { GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, id_)); }

void VertexBuffer::unbind() const noexcept { GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0u)); }
}  // namespace WarriorEngine::Graphics::OpenGL
