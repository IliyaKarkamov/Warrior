#ifndef WARRIOR_TERRAIN_TERRAINLOADER_H
#define WARRIOR_TERRAIN_TERRAINLOADER_H

#include "Engine/Resources/ResourceManager.h"

namespace Warrior::Terrain
{
class Terrain;

class TerrainLoader
{
    WarriorEngine::Resources::ResourceManager& resourceManager_;

public:
    explicit TerrainLoader(WarriorEngine::Resources::ResourceManager& resourceManager);
    std::unique_ptr<Terrain> fromFile(const std::string& terrain) const;
};
}  // namespace Warrior::Terrain

#endif