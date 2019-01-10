#ifndef WARRIOR_ENGINE_RESOURCES_LOADERS_PROGRAMLOADER_H
#define WARRIOR_ENGINE_RESOURCES_LOADERS_PROGRAMLOADER_H

#include "Engine/EngineAPI.h"
#include "Engine/Graphics/OpenGL/Program.h"
#include <memory>

namespace WarriorEngine::Resources::Loaders
{
class WE_API ProgramLoader
{
public:
    std::unique_ptr<Graphics::OpenGL::Program> fromFiles(const std::string& vertexShaderFile,
                                                         const std::string& fragmentShaderFile) const;
};
}  // namespace WarriorEngine::Resources::Loaders

#endif