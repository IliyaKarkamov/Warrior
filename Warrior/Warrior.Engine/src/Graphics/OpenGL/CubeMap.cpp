#include "Engine/Graphics/OpenGL/CubeMap.h"
#include <GL/glew.h>
#include "Utils/ErrorHandler.h"
#include "Engine/Graphics/OpenGL/Texture.h"

namespace WarriorEngine::Graphics::OpenGL
{
CubeMap::CubeMap(const CubMapFace* faces, const int faceCount)
{
    GL_CALL(glGenTextures(1, &id_));
    GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, id_));

    GLenum format;

    for (auto i = 0; i < faceCount; ++i)
    {
        const auto& face = faces[i];

        if (face.bpp == 1)
            format = GL_RED;
        else if (face.bpp == 3)
            format = GL_RGB;
        else if (face.bpp == 4)
            format = GL_RGBA;
        else
            format = GL_RGBA;

        GL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, face.width, face.height, 0,
                             format, GL_UNSIGNED_BYTE, face.bufferImage));
    }

    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

    GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0u));
}

CubeMap::CubeMap(CubeMap&& other) noexcept
{
    id_ = other.id_;
    other.id_ = 0u;
}

CubeMap& CubeMap::operator=(CubeMap&& other) noexcept
{
    if (id_ != other.id_)
    {
        destroy();
        id_ = other.id_;
    }

    return *this;
}

CubeMap::~CubeMap() noexcept { destroy(); }

void CubeMap::bind(const unsigned unit) noexcept
{
    activeUnit_ = unit;
    GL_CALL(glActiveTexture(GL_TEXTURE0 + unit));
    GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, id_));
}

void CubeMap::unbind() noexcept
{
    GL_CALL(glActiveTexture(GL_TEXTURE0 + activeUnit_));
    GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0u));
    activeUnit_ = 0u;
}

void CubeMap::destroy() const noexcept
{
    if (id_ == 0u)
        return;

    GL_CALL(glDeleteTextures(1, &id_));
}

void CubeMap::setWrapping(const TextureWrapping s) noexcept
{
    bind(activeUnit_);
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, static_cast<int>(s)));
}

void CubeMap::setWrapping(const TextureWrapping s, const TextureWrapping t) noexcept
{
    bind(activeUnit_);
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, static_cast<int>(s)));
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, static_cast<int>(t)));
}

void CubeMap::setWrapping(const TextureWrapping s, const TextureWrapping t, const TextureWrapping r) noexcept
{
    bind(activeUnit_);
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, static_cast<int>(s)));
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, static_cast<int>(t)));
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, static_cast<int>(r)));
}

void CubeMap::setFilters(const TextureFilter min, const TextureFilter mag) noexcept
{
    bind(activeUnit_);
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, static_cast<int>(min)));
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, static_cast<int>(mag)));
}
}  // namespace WarriorEngine::Graphics::OpenGL
