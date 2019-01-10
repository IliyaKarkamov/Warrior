#ifndef WARRIOR_ENGINE_RESOURCES_LOADERS_INPUTLISTENERLOADER_H
#define WARRIOR_ENGINE_RESOURCES_LOADERS_INPUTLISTENERLOADER_H

#include "Engine/EngineAPI.h"
#include "Engine/Input/InputListener.h"

namespace WarriorEngine::Resources::Loaders
{
class WE_API InputListenerLoader
{
public:
    std::unique_ptr<Input::InputListener> fromFile(const std::string& file) const;
};
}  // namespace WarriorEngine::Resources::Loaders

#endif