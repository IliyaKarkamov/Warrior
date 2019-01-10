#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_CULLFACEMODE_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_CULLFACEMODE_H

namespace WarriorEngine::Graphics::OpenGL
{
enum class CullFaceMode
{
    Front = 0x0404,
    Back = 0x0405,
    FrontAndBack = 0x0408
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
