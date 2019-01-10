#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_DEPTHFUNC_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_DEPTHFUNC_H

namespace WarriorEngine::Graphics::OpenGL
{
enum class DepthFunc
{
    Never = 0x0200,
    Less = 0x0201,
    Equal = 0x0202,
    LEqual = 0x0203,
    Greater = 0x0204,
    NotEqual = 0x0205,
    GEqual = 0x0206,
    Always = 0x0207
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
