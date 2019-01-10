#include "TerrainLoader.h"
#include "Terrain/Terrain.h"
#include "Engine/Logging/Logging.h"
#include "nlohmann/json.hpp"
#include <filesystem>
#include <fstream>
#include <Engine/Graphics/OpenGL/glm/ext/matrix_transform.inl>

bool readVec3f(const nlohmann::json& src, glm::vec3& dest)
{
    try
    {
        if (src.is_null() || !src.is_array())
        {
            WE_ENGINE_ERROR("Warior.Engine.Resources.Loaders error: Error while trying to read array.");
            return false;
        }

        // x
        {
            auto& x = src[0];

            if (x.is_null() || !x.is_number_float())
            {
                WE_ENGINE_ERROR("Warior.Engine.Resources.Loaders error: array values must be of "
                                "type float.");
                return false;
            }

            dest.x = x.get<float>();
        }

        // y
        {
            auto& y = src[1];

            if (y.is_null() || !y.is_number_float())
            {
                WE_ENGINE_ERROR("Warior.Engine.Resources.Loaders error: array values must be of "
                                "type float.");
                return false;
            }

            dest.y = y.get<float>();
        }

        // z
        {
            auto& z = src[2];

            if (z.is_null() || !z.is_number_float())
            {
                WE_ENGINE_ERROR("Warior.Engine.Resources.Loaders error: array values must be of "
                                "type float.");
                return false;
            }

            dest.z = z.get<float>();
        }
    }
    catch (const std::exception& e)
    {
        WE_ENGINE_ERROR("Warior.Engine.Resources.Loaders error: %s", e.what());
        return false;
    }

    return true;
}

namespace Warrior::Terrain
{
TerrainLoader::TerrainLoader(WarriorEngine::Resources::ResourceManager& resourceManager)
    : resourceManager_(resourceManager)
{}

std::unique_ptr<Terrain> TerrainLoader::fromFile(const std::string& terrain) const
{
    using nlohmann::json;
    using std::filesystem::path;
    using Texture = WarriorEngine::Resources::Resource<WarriorEngine::Graphics::OpenGL::Texture>;
    using Program = WarriorEngine::Resources::Resource<WarriorEngine::Graphics::OpenGL::Program>;

    auto file = path(resourceManager_.getResourcesPath()) / path(terrain);

    if (!exists(file))
    {
        WE_ERROR("Warior.Terrain.TerrainLoader error: Error while trying to read input file: %s",
                 file.string().c_str());
        return nullptr;
    }

    std::ifstream ifs(file.string());

    if (!ifs.is_open())
    {
        WE_ERROR("Warior.Terrain.TerrainLoader error: Error while trying to read input file: %s",
                 file.c_str());
        return nullptr;
    }

    json j;
    ifs >> j;

    std::vector<std::pair<Texture, std::string>> diffuseTextures;
    Texture height;
    Program program;
    int size, vertexCount;
    float maxHeight;

    glm::vec3 position;

    {
        auto& diffuseTexture = j["diffuse_textures"];

        if (diffuseTexture.is_null() || !diffuseTexture.is_array())
        {
            WE_ERROR("Warior.Terrain.TerrainLoader error: Error while trying to read diffuse textures.");
            return nullptr;
        }

        for (auto it = diffuseTexture.begin(); it != diffuseTexture.end(); ++it)
        {
            auto& textureFile = it.value();

            if (!textureFile.is_string())
                continue;

            auto texture = resourceManager_.getTexture(textureFile.get<std::string>());
            diffuseTextures.emplace_back(std::move(texture), "texture_diffuse");
        }
    }

    {
        auto& heightTexture = j["height_texture"];

        if (heightTexture.is_null() || !heightTexture.is_string())
        {
            WE_ERROR("Warior.Terrain.TerrainLoader error: Error while trying to read height texture file.");
            return nullptr;
        }

        height = resourceManager_.getTexture(heightTexture.get<std::string>());
    }

    {
        auto& shaders = j["shaders"];

        if (shaders.is_null() || !shaders.is_string())
        {
            WE_ERROR("Warior.Terrain.TerrainLoader error: Error while trying to read shaders file.");
            return nullptr;
        }

        program = resourceManager_.getProgram(shaders.get<std::string>());
    }

    {
        auto& jsize = j["size"];

        if (jsize.is_null() || !jsize.is_number())
        {
            WE_ERROR("Warior.Terrain.TerrainLoader error: Error while trying to read size.");
            return nullptr;
        }

        size = jsize.get<int>();
    }

    {
        auto& jmaxHeight = j["maxHeight"];

        if (jmaxHeight.is_null() || !jmaxHeight.is_number())
        {
            WE_ERROR("Warior.Terrain.TerrainLoader error: Error while trying to read maxHeight.");
            return nullptr;
        }

        maxHeight = jmaxHeight.get<int>();
    }

    {
        auto& jvertexCount = j["vertexCount"];

        if (jvertexCount.is_null() || !jvertexCount.is_number())
        {
            WE_ERROR("Warior.Terrain.TerrainLoader error: Error while trying to read vertexCount.");
            return nullptr;
        }

        vertexCount = jvertexCount.get<int>();
    }

    if (!readVec3f(j["position"], position))
        return nullptr;

    const auto modelMatrix = glm::translate(glm::mat4(1.f), position);

    return std::make_unique<Terrain>(program, diffuseTextures, height, size, maxHeight, vertexCount,
                                     modelMatrix);
}

}  // namespace Warrior::Terrain
