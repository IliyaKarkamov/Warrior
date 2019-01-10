#include "Engine/Resources/Loaders/CubeMapLoader.h"
#include "Engine/Logging/Logging.h"
#include "stb_image/stb_image.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace WarriorEngine::Resources::Loaders
{
bool readString(const nlohmann::json& j, std::string& value)
{
    if (j.is_null() || !j.is_string())
    {
        WE_ENGINE_ERROR("Warior.Engine.Resources.Loaders.CubeMapLoader error: value must be string");
        return false;
    }

    value = j.get<std::string>();
    return true;
}

std::unique_ptr<Graphics::OpenGL::CubeMap> CubeMapLoader::fromFile(const std::string& file) const
{
    std::ifstream ifs(file);

    if (!ifs.is_open())
    {
        WE_ENGINE_ERROR(
            "Warior.Engine.Resources.Loaders.CameraLoader error: Error while trying to read cubemap file: %s",
            file.c_str());
        return nullptr;
    }

    nlohmann::json j;
    ifs >> j;

    std::vector<std::string> textures;
    textures.reserve(6);

    // right
    if (auto& val = textures.emplace_back(); !readString(j["right"], val))
        return nullptr;

    // left
    if (auto& val = textures.emplace_back(); !readString(j["left"], val))
        return nullptr;

    // top
    if (auto& val = textures.emplace_back(); !readString(j["top"], val))
        return nullptr;

    // bottom
    if (auto& val = textures.emplace_back(); !readString(j["bottom"], val))
        return nullptr;

    // front
    if (auto& val = textures.emplace_back(); !readString(j["front"], val))
        return nullptr;

    // back
    if (auto& val = textures.emplace_back(); !readString(j["back"], val))
        return nullptr;

    const auto directory = fs::path(file).parent_path();

    std::vector<Graphics::OpenGL::CubMapFace> faces;
    faces.reserve(6);

    for (auto&& texture : textures)
    {
        int width, height, bpp;

        const auto imageBuffer =
            stbi_load((directory / fs::path(texture)).string().c_str(), &width, &height, &bpp, 0);

        if (!imageBuffer)
        {
            WE_ENGINE_ERROR("Warrior.Engine.Resources.Loaders.CubeMapLoader error: texture loading failed.");
            return nullptr;
        }

        faces.emplace_back(imageBuffer, width, height, bpp);
    }

    auto cubeMap = std::make_unique<Graphics::OpenGL::CubeMap>(&faces[0], faces.size());

    for (auto&& face : faces)
        stbi_image_free(face.bufferImage);

    return cubeMap;
}
}  // namespace WarriorEngine::Resources::Loaders
