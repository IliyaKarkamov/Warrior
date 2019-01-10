#ifndef WARRIOR_ENGINE_RESOURCES_LOADERS_MODELLOADER_H
#define WARRIOR_ENGINE_RESOURCES_LOADERS_MODELLOADER_H

#include "Engine/EngineAPI.h"
#include "Engine/Graphics/Model.h"
#include <memory>

namespace WarriorEngine::Resources
{
class ResourceManager;
}

namespace WarriorEngine::Resources::Loaders
{
namespace detail
{
class ModelLoaderImpl;
}

class WE_API ModelLoader
{
    std::shared_ptr<detail::ModelLoaderImpl> pImpl_ = nullptr;

public:
    explicit ModelLoader(ResourceManager* manager);
    std::unique_ptr<Graphics::Model> fromFile(const std::string& file) const;
};
}  // namespace WarriorEngine::Resources::Loaders

#endif