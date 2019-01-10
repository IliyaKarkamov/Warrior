#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_BUFFERUSAGE_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_BUFFERUSAGE_H

namespace WarriorEngine::Graphics::OpenGL
{
enum class BufferUsage
{
    StreamDraw = 0x88E0,
    StreamRead = 0x88E1,
    StreamCopy = 0x88E2,
    StaticDraw = 0x88E4,
    StaticRead = 0x88E5,
    StaticCopy = 0x88E6,
    DynamicDraw = 0x88E8,
    DynamicRead = 0x88E9,
    DynamicCopy = 0x88EA
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
