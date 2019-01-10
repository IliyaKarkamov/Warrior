#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_TEXTURE_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_TEXTURE_H

#include "Engine/EngineAPI.h"
#include "Engine/Graphics/OpenGL/enums/TextureWrapping.h"
#include "Engine/Graphics/OpenGL/enums/TextureFilter.h"
#include "glm/vec4.hpp"
#include <vector>

namespace WarriorEngine::Graphics::OpenGL
{
class WE_API Texture
{
    unsigned int id_;

    int width_;
    int height_;
    int bpp_;

    unsigned int activeUnit_ = 0u;
    std::vector<unsigned char> imageBuffer_;

public:
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(const unsigned char* imageBuffer, const int width, const int height, const int bpp);

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    ~Texture() noexcept;

    int getWidth() const noexcept;
    int getHeight() const noexcept;
    int getBitsPerPixel() const noexcept;

    int getRgbValue(const int x, const int y) const noexcept;

    void bind(const unsigned int unit = 0) noexcept;
    void unbind() noexcept;

    void setWrapping(const TextureWrapping s) noexcept;
    void setWrapping(const TextureWrapping s, const TextureWrapping t) noexcept;
    void setWrapping(const TextureWrapping s, const TextureWrapping t, const TextureWrapping r) noexcept;

    void setFilters(const TextureFilter min, const TextureFilter mag) noexcept;
    void setBorderColor(const glm::vec4& color) noexcept;

private:
    void destroy() const noexcept;
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
