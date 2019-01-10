#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_BLENDINGEQUATION_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_BLENDINGEQUATION_H

namespace WarriorEngine::Graphics::OpenGL
{
enum class BlendingEquation
{
    FuncAdd = 0x8006,
    FuncSubtract = 0x800A,
    FuncReverseSubtract = 0x800B,
    Min = 0x8007,
    Max = 0x8008
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
