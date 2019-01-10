#ifndef WARRIOR_ENGINE_RESOURCES_RESOURCEMANAGER_H
#define WARRIOR_ENGINE_RESOURCES_RESOURCEMANAGER_H

#include "Engine/EngineAPI.h"
#include "Engine/Resources/Resources.h"
#include "Engine/Graphics/OpenGL/Texture.h"
#include "Engine/Graphics/OpenGL/Program.h"
#include "Engine/Graphics/OpenGL/CubeMap.h"
#include "Engine/Graphics/Model.h"
#include "Engine/Graphics/Camera.h"
#include "Engine/Input/InputListener.h"
#include <string>
#include <shared_mutex>

namespace WarriorEngine::Resources
{
class WE_API ResourceManager
{
    std::string resourcesPath_;

    std::shared_mutex texturesMutex_;
    Resources<Graphics::OpenGL::Texture> textures_;

    std::shared_mutex programsMutex_;
    Resources<Graphics::OpenGL::Program> programs_;

    std::shared_mutex modelsMutex_;
    Resources<Graphics::Model> models_;

    std::shared_mutex inputListenersMutex_;
    Resources<Input::InputListener> inputListeners_;

    std::shared_mutex camerasMutex_;
    Resources<Graphics::Camera> cameras_;

    std::shared_mutex cubeMapsMutex_;
    Resources<Graphics::OpenGL::CubeMap> cubeMaps_;

public:
    ResourceManager() = default;
    ResourceManager(std::string resourcesPath);

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    void setResourcesPath(const std::string& path);
    std::string getResourcesPath() const noexcept { return resourcesPath_; }

    Resource<Graphics::OpenGL::Texture> getTexture(const std::string& texture);
    Resource<Graphics::OpenGL::Program> getProgram(const std::string& program);
    Resource<Graphics::Model> getModel(const std::string& model);
    Resource<Input::InputListener> getInputListener(const std::string& listener);
    Resource<Graphics::Camera> getCamera(const std::string& camera);
    Resource<Graphics::OpenGL::CubeMap> getCubeMap(const std::string& cubeMap);

    void update();
};
}  // namespace WarriorEngine::Resources

#endif