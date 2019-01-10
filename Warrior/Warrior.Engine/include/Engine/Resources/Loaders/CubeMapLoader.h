#ifndef WARRIOR_ENGINE_RESOURCES_LOADERS_CUBEMAPLOADER_H
#define WARRIOR_ENGINE_RESOURCES_LOADERS_CUBEMAPLOADER_H

#include "Engine/EngineAPI.h"
#include "Engine/Graphics/OpenGL/CubeMap.h"
#include <memory>
#include <string>

namespace WarriorEngine::Resources::Loaders
{
class WE_API CubeMapLoader
{
public:
    std::unique_ptr<Graphics::OpenGL::CubeMap> fromFile(const std::string& file) const;
};
}  // namespace WarriorEngine::Resources::Loaders

#endif