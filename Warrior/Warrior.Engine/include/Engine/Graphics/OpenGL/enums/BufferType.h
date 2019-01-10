#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_BUFFERTYPE_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_BUFFERTYPE_H

namespace WarriorEngine::Graphics::OpenGL
{
enum class BufferType
{
    Color = 0x00004000,
    Depth = 0x00000100,
    Stencil = 0x00000400
};

inline BufferType operator|(const BufferType lhs, const BufferType rhs)
{
    return static_cast<BufferType>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs));
}

}  // namespace WarriorEngine::Graphics::OpenGL

#endif
