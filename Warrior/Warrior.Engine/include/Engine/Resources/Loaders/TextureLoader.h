#ifndef WARRIOR_ENGINE_RESOURCES_LOADERS_TEXTURELOADER_H
#define WARRIOR_ENGINE_RESOURCES_LOADERS_TEXTURELOADER_H

#include "Engine/EngineAPI.h"
#include "Engine/Graphics/OpenGL/Texture.h"
#include <memory>
#include <string>

namespace WarriorEngine::Resources::Loaders
{
class WE_API TextureLoader
{
public:
    std::unique_ptr<Graphics::OpenGL::Texture> fromFile(const std::string& file) const;
};
}  // namespace WarriorEngine::Resources::Loaders

#endif