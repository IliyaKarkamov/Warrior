#include "Engine/Graphics/OpenGL/VertexBufferLayout.h"

#include <GL/glew.h>
#include "Engine/Core.h"

namespace WarriorEngine::Graphics::OpenGL
{
int VertexBufferElement::getSizeOfType(const unsigned type) noexcept
{
    switch (type)
    {
    case GL_FLOAT:
        return 4;
    case GL_UNSIGNED_INT:
        return 4;
    case GL_UNSIGNED_BYTE:
        return 1;
    }

    ASSERT(false);
    return 0;
}

template<typename T>
void VertexBufferLayout::push(const int count) noexcept
{
    static_assert(false);
}

template<>
void VertexBufferLayout::push<float>(const int count) noexcept
{
    elements_.push_back({GL_FLOAT, count, false});
    stride_ += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

const std::vector<VertexBufferElement>& VertexBufferLayout::getElements() const noexcept { return elements_; }

int VertexBufferLayout::getStride() const noexcept { return stride_; }
}  // namespace WarriorEngine::Graphics::OpenGL
