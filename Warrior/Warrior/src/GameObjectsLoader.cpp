#include "GameObjectsLoader.h"

#include <Engine/Logging/Logging.h>
#include <Engine/Graphics/OpenGL/glm/ext/matrix_transform.inl>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

extern bool readVec3f(const nlohmann::json& src, glm::vec3& dest);

GameObjectsLoader::GameObjectsLoader(WarriorEngine::Resources::ResourceManager& resourceManager)
    : resourceManager_(resourceManager)
{}

std::vector<GameObject> GameObjectsLoader::fromFile(const std::string& filename) const
{
    using nlohmann::json;
    using std::filesystem::path;
    using Program = WarriorEngine::Resources::Resource<WarriorEngine::Graphics::OpenGL::Program>;
    using Model = WarriorEngine::Resources::Resource<WarriorEngine::Graphics::Model>;

    auto file = path(resourceManager_.getResourcesPath()) / path(filename);

    if (!exists(file))
    {
        WE_ERROR("Warior.GameObjectsLoader error: Error while trying to read input file: %s",
                 file.string().c_str());
        return {};
    }

    std::ifstream ifs(file.string());

    if (!ifs.is_open())
    {
        WE_ERROR("Warior.GameObjectsLoader error: Error while trying to read input file: %s", file.c_str());
        return {};
    }

    json j;
    ifs >> j;

    if (!j.is_array())
        return {};

    std::vector<GameObject> gameObjects;
    gameObjects.reserve(j.size());

    for (auto it = j.begin(); it != j.end(); ++it)
    {
        auto& gameObject = it.value();

        if (!gameObject.is_object())
            continue;

        Program program;
        Model model;
        glm::vec3 position;
        glm::vec3 scale;

        {
            auto& shaders = gameObject["program"];

            if (shaders.is_null() || !shaders.is_string())
            {
                WE_ERROR("Warior.GameObjectsLoader error: Error while trying to read program file.");
                continue;
            }

            program = resourceManager_.getProgram(shaders.get<std::string>());
        }

        {
            auto& jmodel = gameObject["model"];

            if (jmodel.is_null() || !jmodel.is_string())
            {
                WE_ERROR("Warior.GameObjectsLoader error: Error while trying to read model file.");
                continue;
            }

            model = resourceManager_.getModel(jmodel.get<std::string>());
        }

        if (!readVec3f(gameObject["position"], position))
            continue;

        if (!readVec3f(gameObject["scale"], scale))
            continue;

        auto modelMatrix = translate(glm::mat4(1.f), position);
        modelMatrix = glm::scale(modelMatrix, scale);

        gameObjects.emplace_back(std::move(program), std::move(model), modelMatrix);
    }

    return gameObjects;
}
