#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_TEXTUREWRAPPING_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_TEXTUREWRAPPING_H

namespace WarriorEngine::Graphics::OpenGL
{
enum class TextureWrapping
{
    ClampEdge = 0x812F,
    ClampBorder = 0x812D,
    Repeat = 0x2901,
    MirroredRepeat = 0x8370
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
