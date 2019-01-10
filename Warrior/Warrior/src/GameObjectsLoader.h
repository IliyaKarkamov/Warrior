#ifndef WARRIOR_GAME_OBJECTS_LOADER_H
#define WARRIOR_GAME_OBJECTS_LOADER_H

#include <vector>
#include "GameObject.h"
#include <Engine/Resources/ResourceManager.h>

class GameObjectsLoader
{
    WarriorEngine::Resources::ResourceManager& resourceManager_;

public:
    explicit GameObjectsLoader(WarriorEngine::Resources::ResourceManager& resourceManager);
    std::vector<GameObject> fromFile(const std::string& filename) const;
};

#endif