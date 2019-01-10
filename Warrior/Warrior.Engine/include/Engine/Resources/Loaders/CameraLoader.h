#ifndef WARRIOR_ENGINE_RESOURCES_LOADERS_CAMERALOADER_H
#define WARRIOR_ENGINE_RESOURCES_LOADERS_CAMERALOADER_H

#include "Engine/EngineAPI.h"
#include "Engine/Graphics/Camera.h"
#include <memory>
#include <string>

namespace WarriorEngine::Resources::Loaders
{
class WE_API CameraLoader
{
public:
    std::unique_ptr<Graphics::Camera> fromFile(const std::string& file) const;
};
}  // namespace WarriorEngine::Resources::Loaders

#endif