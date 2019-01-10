#ifndef WARRIOR_ENGINE_RESOURCES_RESOURCES_H
#define WARRIOR_ENGINE_RESOURCES_RESOURCES_H

#include <memory>
#include <unordered_map>

namespace WarriorEngine::Resources
{
template<typename T>
using Resource = std::shared_ptr<T>;

template<typename T>
using Resources = std::unordered_map<std::string, Resource<T>>;
}  // namespace WarriorEngine::Resources

#endif