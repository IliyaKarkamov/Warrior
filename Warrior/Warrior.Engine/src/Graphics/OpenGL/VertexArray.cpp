#include "Engine/Graphics/OpenGL/VertexArray.h"
#include "Engine/Core.h"
#include "Engine/Graphics/OpenGL/VertexBufferLayout.h"
#include "Engine/Graphics/OpenGL/VertexBuffer.h"
#include "Utils/ErrorHandler.h"
#include <GL/glew.h>

namespace WarriorEngine::Graphics::OpenGL
{
VertexArray::VertexArray() noexcept : id_(0u) { GL_CALL(glGenVertexArrays(1, &id_)); }

VertexArray::~VertexArray() noexcept { destroy(); }

VertexArray::VertexArray(VertexArray&& other) noexcept
{
    id_ = other.id_;
    other.id_ = 0u;
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
    if (id_ != other.id_)
    {
        destroy();
        id_ = other.id_;
    }

    return *this;
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const noexcept
{
    bind();
    vb.bind();

    const auto& elements = layout.getElements();

    auto offset = 0u;

    for (auto i = 0u; i < elements.size(); ++i)
    {
        const auto& element = elements[i];
        
        GL_CALL(glVertexAttribPointer(i,
                                      element.count,
                                      element.type,
                                      element.normalized ? GL_TRUE : GL_FALSE,
                                      layout.getStride(),
                                      reinterpret_cast<const void*>(offset)));
        GL_CALL(glEnableVertexAttribArray(i));

        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind() const noexcept { GL_CALL(glBindVertexArray(id_)); }

void VertexArray::unbind() const noexcept { GL_CALL(glBindVertexArray(0u)); }

void VertexArray::destroy() const noexcept
{
    if (id_ == 0u)
        return;

    GL_CALL(glDeleteVertexArrays(1, &id_));
}
}  // namespace WarriorEngine::Graphics::OpenGL
