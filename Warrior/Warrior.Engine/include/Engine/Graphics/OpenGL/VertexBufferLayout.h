#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_VERTEXBUFFERLAYOUT_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_VERTEXBUFFERLAYOUT_H

#include "Engine/EngineAPI.h"
#include <vector>

namespace WarriorEngine::Graphics::OpenGL
{
struct WE_API VertexBufferElement
{
    unsigned int type;
    int count;
    bool normalized;

    static int getSizeOfType(const unsigned type) noexcept;
};

class WE_API VertexBufferLayout
{
    std::vector<VertexBufferElement> elements_;
    int stride_ = 0;

public:
    template<typename T>
    void push(const int count) noexcept;

    template<>
    void push<float>(const int count) noexcept;

    const std::vector<VertexBufferElement>& getElements() const noexcept;
    int getStride() const noexcept;
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif