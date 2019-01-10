#include "Engine/Resources/ResourceManager.h"
#include "Engine/Logging/Logging.h"
#include "Engine/Resources/Loaders/TextureLoader.h"
#include "Engine/Resources/Loaders/ProgramLoader.h"
#include "Engine/Resources/Loaders/ModelLoader.h"
#include "Engine/Resources/Loaders/InputListenerLoader.h"
#include "Engine/Resources/Loaders/CameraLoader.h"
#include "Engine/Resources/Loaders/CubeMapLoader.h"
#include <experimental/filesystem>
#include <utility>

namespace fs = std::experimental::filesystem;

namespace WarriorEngine::Resources
{
ResourceManager::ResourceManager(std::string resourcesPath) : resourcesPath_(std::move(resourcesPath)) {}

void ResourceManager::setResourcesPath(const std::string& path) { resourcesPath_ = path; }

Resource<Graphics::OpenGL::Texture> ResourceManager::getTexture(const std::string& texture)
{
    std::shared_lock<std::shared_mutex> sharedLock(texturesMutex_);

    if (const auto it = textures_.find(texture); it != textures_.end())
        return it->second;

    sharedLock.unlock();
    std::unique_lock<std::shared_mutex> writeLock(texturesMutex_);

    if (const auto it = textures_.find(texture); it != textures_.end())
        return it->second;

    const auto filePath = fs::path(resourcesPath_) / fs::path(texture);

    if (!fs::exists(filePath))
    {
        WE_ENGINE_ERROR(
            "Warrior.Engine.Resources.ResourceManager error: texture file doesn't exists. Filepath: %s",
            filePath.string().c_str());
        return nullptr;
    }

    Loaders::TextureLoader textureLoader;
    textures_[texture] = textureLoader.fromFile(filePath.string());

    return textures_[texture];
}

Resource<Graphics::OpenGL::Program> ResourceManager::getProgram(const std::string& program)
{
    std::shared_lock<std::shared_mutex> sharedLock(programsMutex_);

    if (const auto it = programs_.find(program); it != programs_.end())
        return it->second;

    sharedLock.unlock();
    std::unique_lock<std::shared_mutex> writeLock(programsMutex_);

    if (const auto it = programs_.find(program); it != programs_.end())
        return it->second;

    const auto basePath = fs::path(resourcesPath_) / fs::path(program);
    const auto vertexShader = basePath.string() + ".vert";
    const auto fragmentShader = basePath.string() + ".frag";

    if (!fs::exists(vertexShader) || !fs::exists(fragmentShader))
    {
        WE_ENGINE_ERROR("Warrior.Engine.Resources.ResourceManager error: shader program file doesn't exists. "
                        "Vertex shader: %s, Fragment shader: %s",
                        vertexShader.c_str(), fragmentShader.c_str());
        return nullptr;
    }

    Loaders::ProgramLoader programLoader;
    programs_[program] = programLoader.fromFiles(vertexShader, fragmentShader);

    return programs_[program];
}

Resource<Graphics::Model> ResourceManager::getModel(const std::string& model)
{
    std::shared_lock<std::shared_mutex> sharedLock(modelsMutex_);

    if (const auto it = models_.find(model); it != models_.end())
        return it->second;

    sharedLock.unlock();
    std::unique_lock<std::shared_mutex> writeLock(modelsMutex_);

    if (const auto it = models_.find(model); it != models_.end())
        return it->second;

    const auto filePath = fs::path(resourcesPath_) / fs::path(model);

    if (!fs::exists(filePath))
    {
        WE_ENGINE_ERROR(
            "Warrior.Engine.Resources.ResourceManager error: model file doesn't exists. Filepath: %s",
            filePath.string().c_str());
        return nullptr;
    }

    Loaders::ModelLoader modelLoader(this);
    models_[model] = modelLoader.fromFile(filePath.string());

    return models_[model];
}

Resource<Input::InputListener> ResourceManager::getInputListener(const std::string& listener)
{
    std::shared_lock<std::shared_mutex> sharedLock(inputListenersMutex_);

    if (const auto it = inputListeners_.find(listener); it != inputListeners_.end())
        return it->second;

    sharedLock.unlock();
    std::unique_lock<std::shared_mutex> writeLock(inputListenersMutex_);

    if (const auto it = inputListeners_.find(listener); it != inputListeners_.end())
        return it->second;

    const auto filePath = fs::path(resourcesPath_) / fs::path(listener);

    if (!fs::exists(filePath))
    {
        WE_ENGINE_ERROR("Warrior.Engine.Resources.ResourceManager error: input listener file doesn't exists. "
                        "Filepath: %s",
                        filePath.string().c_str());
        return nullptr;
    }

    Loaders::InputListenerLoader inputLoader;
    inputListeners_[listener] = inputLoader.fromFile(filePath.string());

    return inputListeners_[listener];
}

Resource<Graphics::Camera> ResourceManager::getCamera(const std::string& camera)
{
    std::shared_lock<std::shared_mutex> sharedLock(camerasMutex_);

    if (const auto it = cameras_.find(camera); it != cameras_.end())
        return it->second;

    sharedLock.unlock();
    std::unique_lock<std::shared_mutex> writeLock(camerasMutex_);

    if (const auto it = cameras_.find(camera); it != cameras_.end())
        return it->second;

    const auto filePath = fs::path(resourcesPath_) / fs::path(camera);

    if (!fs::exists(filePath))
    {
        WE_ENGINE_ERROR("Warrior.Engine.Resources.ResourceManager error: input listener file doesn't exists. "
                        "Filepath: %s",
                        filePath.string().c_str());
        return nullptr;
    }

    Loaders::CameraLoader cameraLoader;
    cameras_[camera] = cameraLoader.fromFile(filePath.string());

    return cameras_[camera];
}

Resource<Graphics::OpenGL::CubeMap> ResourceManager::getCubeMap(const std::string& cubeMap)
{
    std::shared_lock<std::shared_mutex> sharedLock(cubeMapsMutex_);

    if (const auto it = cubeMaps_.find(cubeMap); it != cubeMaps_.end())
        return it->second;

    sharedLock.unlock();
    std::unique_lock<std::shared_mutex> writeLock(cubeMapsMutex_);

    if (const auto it = cubeMaps_.find(cubeMap); it != cubeMaps_.end())
        return it->second;

    const auto filePath = fs::path(resourcesPath_) / fs::path(cubeMap);

    if (!fs::exists(filePath))
    {
        WE_ENGINE_ERROR("Warrior.Engine.Resources.ResourceManager error: cube map file doesn't exists. "
                        "Filepath: %s",
                        filePath.string().c_str());
        return nullptr;
    }

    Loaders::CubeMapLoader cubeMapLoader;
    cubeMaps_[cubeMap] = cubeMapLoader.fromFile(filePath.string());

    return cubeMaps_[cubeMap];
}

void ResourceManager::update()
{
    {
        std::lock_guard<std::shared_mutex> _(texturesMutex_);

        for (auto it = textures_.begin(); it != textures_.end();)
        {
            if (it->second.use_count() <= 1)
                it = textures_.erase(it);
            else
                ++it;
        }
    }
}
}  // namespace WarriorEngine::Resources
