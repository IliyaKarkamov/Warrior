#include "Engine/Graphics/OpenGL/Texture.h"
#include "Engine/Core.h"
#include "Engine/Logging/Logging.h"
#include "Utils/ErrorHandler.h"
#include <GL/glew.h>

namespace WarriorEngine::Graphics::OpenGL
{
Texture::Texture(const unsigned char* imageBuffer, const int width, const int height, const int bpp)
    : id_(0u), width_(width), height_(height), bpp_(bpp)
{
    GL_CALL(glGenTextures(1, &id_));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, id_));

    GLenum format;

    if (bpp == 1)
        format = GL_RED;
    else if (bpp == 3)
        format = GL_RGB;
    else if (bpp == 4)
        format = GL_RGBA;
    else
        format = GL_RGBA;

    GL_CALL(
        glTexImage2D(GL_TEXTURE_2D, 0, format, width_, height_, 0, format, GL_UNSIGNED_BYTE, imageBuffer));
    GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));

    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0u));

    const auto size = width * height * bpp;
    std::vector<unsigned char> vec(imageBuffer, imageBuffer + size);
    imageBuffer_.swap(vec);
}

Texture::Texture(Texture&& other) noexcept : id_(0u), width_(0), height_(0), bpp_(0)
{
    id_ = other.id_;
    other.id_ = 0u;

    width_ = other.width_;
    height_ = other.height_;
    bpp_ = other.bpp_;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    if (id_ != other.id_)
    {
        destroy();
        id_ = other.id_;

        width_ = other.width_;
        height_ = other.height_;
        bpp_ = other.bpp_;
    }

    return *this;
}

Texture::~Texture() noexcept { destroy(); }

int Texture::getWidth() const noexcept { return width_; }

int Texture::getHeight() const noexcept { return height_; }

int Texture::getBitsPerPixel() const noexcept { return bpp_; }

int Texture::getRgbValue(const int x, const int y) const noexcept
{
    const auto pixelOffset = &imageBuffer_[0] + (x + height_ * y) * bpp_;
    const auto r = pixelOffset[0];
    const auto g = pixelOffset[1];
    const auto b = pixelOffset[2];

    int rgb = r;
    rgb = (rgb << 8) + g;
    rgb = (rgb << 8) + b;

    return rgb;
}

void Texture::bind(const unsigned int unit) noexcept
{
    activeUnit_ = unit;
    GL_CALL(glActiveTexture(GL_TEXTURE0 + unit));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, id_));
}

void Texture::unbind() noexcept
{
    GL_CALL(glActiveTexture(GL_TEXTURE0 + activeUnit_));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0u));
    activeUnit_ = 0u;
}

void Texture::setWrapping(const TextureWrapping s) noexcept
{
    bind(activeUnit_);
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(s)));
}

void Texture::setWrapping(const TextureWrapping s, const TextureWrapping t) noexcept
{
    bind(activeUnit_);
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(s)));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(t)));
}

void Texture::setWrapping(const TextureWrapping s, const TextureWrapping t, const TextureWrapping r) noexcept
{
    bind(activeUnit_);
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(s)));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(t)));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, static_cast<int>(r)));
}

void Texture::setFilters(const TextureFilter min, const TextureFilter mag) noexcept
{
    bind(activeUnit_);
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(min)));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(mag)));
}

void Texture::setBorderColor(const glm::vec4& color) noexcept
{
    bind(activeUnit_);
    GL_CALL(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &color[0]));
}

void Texture::destroy() const noexcept
{
    if (id_ == 0u)
        return;

    GL_CALL(glDeleteTextures(1, &id_));
}
}  // namespace WarriorEngine::Graphics::OpenGL