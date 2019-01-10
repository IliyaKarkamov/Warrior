#include "Engine/Resources/Loaders/TextureLoader.h"
#include "Engine/Logging/Logging.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

namespace WarriorEngine::Resources::Loaders
{
std::unique_ptr<Graphics::OpenGL::Texture> TextureLoader::fromFile(const std::string& file) const
{
    //stbi_set_flip_vertically_on_load(1);

    int width, height, bpp;

    const auto imageBuffer = stbi_load(file.c_str(), &width, &height, &bpp, 0);

    if (!imageBuffer)
    {
        WE_ENGINE_ERROR("Warrior.Engine.Resources.Loaders.TextureLoader error: texture loading failed.");
        return nullptr;
    }

    auto ptr = std::make_unique<Graphics::OpenGL::Texture>(imageBuffer, width, height, bpp);

    if (imageBuffer)
        stbi_image_free(imageBuffer);

    return ptr;
}
}  // namespace WarriorEngine::Resources::Loaders
