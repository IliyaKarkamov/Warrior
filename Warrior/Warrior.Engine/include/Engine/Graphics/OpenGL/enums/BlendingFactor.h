#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_BLENDINGFACTOR_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_BLENDINGFACTOR_H

namespace WarriorEngine::Graphics::OpenGL
{
enum class BlendingFactor
{
    Zero = 0,
    One = 1,
    SrcColor = 0x0300,
    OneMinusSrcColor = 0x0301,
    DstColor = 0x0306,
    OneMinusDstColor = 0x0307,
    SrcAlpha = 0x0302,
    OneMinusSrcAlpha = 0x0303,
    DstAlpha = 0x0304,
    OneMinusDstAlpha = 0x0305,
    ConstantColor = 0x8001,
    OneMinusConstantColor = 0x8002,
    ConstantAlpha = 0x8003,
    OneMinusConstantAlpha = 0x8004,
    SrcAlphaSaturate = 0x0308
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
