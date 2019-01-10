#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_CAPABILITY_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_CAPABILITY_H

namespace WarriorEngine::Graphics::OpenGL
{
enum class Capability
{
    Blend = 0x0BE2,
    DepthTest = 0x0B71,
    DepthClamp = 0x864F,
    Dither = 0x0BD0,
    StencilTest = 0x0B90,
    CullFace = 0x0B44
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
