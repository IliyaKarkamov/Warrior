#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_TEXTUREFILTER_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_ENUMS_TEXTUREFILTER_H

namespace WarriorEngine::Graphics::OpenGL
{
enum class TextureFilter
{
    Nearest = 0x2600,
    Linear = 0x2601,
    NearestMipmapNearest = 0x2700,
    LinearMipmapNearest = 0x2701,
    NearestMipmapLinear = 0x2702,
    LinearMipmapLinear = 0x2703
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
