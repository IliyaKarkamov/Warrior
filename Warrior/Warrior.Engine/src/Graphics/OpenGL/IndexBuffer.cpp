#include "Engine/Graphics/OpenGL/IndexBuffer.h"
#include "Engine/Core.h"
#include "Utils/ErrorHandler.h"
#include <GL/glew.h>

namespace WarriorEngine::Graphics::OpenGL
{
IndexBuffer::IndexBuffer(const unsigned int* indices, const int count, const BufferUsage usage) noexcept
    : id_(0u), count_(count)
{
    static_assert(sizeof(unsigned int) == sizeof(GLuint), "sizeof unsigned int != sizeof GLuint");

    GL_CALL(glGenBuffers(1, &id_));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_));
    GL_CALL(glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, static_cast<unsigned int>(usage)));
}

IndexBuffer::~IndexBuffer() noexcept { destroy(); }

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
{
    id_ = other.id_;
    count_ = other.count_;
    other.id_ = 0u;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
    if (id_ != other.id_)
    {
        destroy();
        id_ = other.id_;
        count_ = other.count_;
        other.id_ = 0u;
    }

    return *this;
}

void IndexBuffer::bind() const noexcept { GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_)); }

void IndexBuffer::unbind() const noexcept { GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u)); }

void IndexBuffer::destroy() const noexcept
{
    if (id_ == 0u)
        return;

    GL_CALL(glDeleteBuffers(1, &id_));
}
}  // namespace WarriorEngine::Graphics::OpenGL
