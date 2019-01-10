#include "Engine/Resources/Loaders/CameraLoader.h"
#include "Engine/Logging/Logging.h"
#include <nlohmann/json.hpp>
#include <fstream>

using nlohmann::json;

namespace WarriorEngine::Resources::Loaders
{
bool readVec3f(const json& src, glm::vec3& dest)
{
    try
    {
        if (src.is_null() || !src.is_array())
        {
            WE_ENGINE_ERROR(
                "Warior.Engine.Resources.Loaders.CameraLoader error: Error while trying to read array.");
            return false;
        }

        // x
        {
            auto& x = src[0];

            if (x.is_null() || !x.is_number_float())
            {
                WE_ENGINE_ERROR("Warior.Engine.Resources.Loaders.CameraLoader error: array values must be of "
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
                WE_ENGINE_ERROR("Warior.Engine.Resources.Loaders.CameraLoader error: array values must be of "
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
                WE_ENGINE_ERROR("Warior.Engine.Resources.Loaders.CameraLoader error: array values must be of "
                                "type float.");
                return false;
            }

            dest.z = z.get<float>();
        }
    }
    catch (const std::exception& e)
    {
        WE_ENGINE_ERROR("Warior.Engine.Resources.Loaders.CameraLoader error: %s", e.what());
        return false;
    }

    return true;
}

bool readFloat(const json& src, float& dest)
{
    try
    {
        if (src.is_null() || !src.is_number_float())
        {
            WE_ENGINE_ERROR("Warior.Engine.Resources.Loaders.CameraLoader error: the value is not a float");
            return false;
        }

        dest = src.get<float>();
    }
    catch (const std::exception& e)
    {
        WE_ENGINE_ERROR("Warior.Engine.Resources.Loaders.CameraLoader error: %s", e.what());
        return false;
    }

    return true;
}

bool readBool(const json& src, bool& dest)
{
    try
    {
        if (src.is_null() || !src.is_boolean())
        {
            WE_ENGINE_ERROR("Warior.Engine.Resources.Loaders.CameraLoader error: the value is not a boolean");
            return false;
        }

        dest = src.get<bool>();
    }
    catch (const std::exception& e)
    {
        WE_ENGINE_ERROR("Warior.Engine.Resources.Loaders.CameraLoader error: %s", e.what());
        return false;
    }

    return true;
}

std::unique_ptr<Graphics::Camera> CameraLoader::fromFile(const std::string& file) const
{
    std::ifstream ifs(file);

    if (!ifs.is_open())
    {
        WE_ENGINE_ERROR(
            "Warior.Engine.Resources.Loaders.CameraLoader error: Error while trying to read camera file: %s",
            file.c_str());
        return nullptr;
    }

    json j;
    ifs >> j;

    glm::vec3 position;
    glm::vec3 up;
    float yaw, pitch, speed, zoom;
    bool trailingDirection;

    // position
    if (!readVec3f(j["position"], position))
        return nullptr;

    // up
    if (!readVec3f(j["up"], up))
        return nullptr;

    // yaw
    if (!readFloat(j["yaw"], yaw))
        return nullptr;

    // pitch
    if (!readFloat(j["pitch"], pitch))
        return nullptr;

    // zoom
    if (!readFloat(j["zoom"], zoom))
        return nullptr;

    // trailingOnSameDirection
    if (!readBool(j["trailingDirection"], trailingDirection))
        return nullptr;

    return std::make_unique<Graphics::Camera>(position, up, yaw, pitch, zoom, trailingDirection);
}
}  // namespace WarriorEngine::Resources::Loaders