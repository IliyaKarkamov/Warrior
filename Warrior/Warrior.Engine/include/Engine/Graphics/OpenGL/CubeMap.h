#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_CUBEMAP_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_CUBEMAP_H

#include "Engine/EngineAPI.h"

namespace WarriorEngine::Graphics::OpenGL
{
enum class TextureFilter;
enum class TextureWrapping;

struct CubMapFace
{
    unsigned char* bufferImage;
    int width;
    int height;
    int bpp;

    CubMapFace(unsigned char* buffer, const int width, const int height, const int bpp)
        : bufferImage(buffer), width(width), height(height), bpp(bpp)
    {}
};

class WE_API CubeMap
{
    unsigned int id_ = 0u;
    unsigned int activeUnit_ = 0u;

public:
    CubeMap(const CubeMap&) = delete;
    CubeMap& operator=(const CubeMap&) = delete;

    CubeMap(const CubMapFace* faces, const int faceCount);

    CubeMap(CubeMap&& other) noexcept;
    CubeMap& operator=(CubeMap&& other) noexcept;

    ~CubeMap() noexcept;

    void bind(const unsigned int unit = 0) noexcept;
    void unbind() noexcept;

    void setWrapping(const TextureWrapping s) noexcept;
    void setWrapping(const TextureWrapping s, const TextureWrapping t) noexcept;
    void setWrapping(const TextureWrapping s, const TextureWrapping t, const TextureWrapping r) noexcept;

    void setFilters(const TextureFilter min, const TextureFilter mag) noexcept;

private:
    void destroy() const noexcept;
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
