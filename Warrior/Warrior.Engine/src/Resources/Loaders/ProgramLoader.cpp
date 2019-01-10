#include "Engine/Resources/Loaders/ProgramLoader.h"
#include "Engine/Logging/Logging.h"
#include <fstream>
#include <string>
#include "Engine/Graphics/OpenGL/Shader.h"

namespace WarriorEngine::Resources::Loaders
{
std::unique_ptr<Graphics::OpenGL::Program> ProgramLoader::fromFiles(
    const std::string& vertexShaderFile,
    const std::string& fragmentShaderFile) const
{
    std::string vertexSource, fragmentSource;

    {
        std::ifstream ifs(vertexShaderFile);

        if (!ifs.is_open())
        {
            WE_ENGINE_ERROR(
                "Warrior.Engine.Resoruces.Loaders.ProgramLoader error: cannot open vertex shader file.");
            return nullptr;
        }

        vertexSource.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    }

    {
        std::ifstream ifs(fragmentShaderFile);

        if (!ifs.is_open())
        {
            WE_ENGINE_ERROR(
                "Warrior.Engine.Resoruces.Loaders.ProgramLoader error: cannot open fragment shader file.");
            return nullptr;
        }

        fragmentSource.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    }

    Graphics::OpenGL::Shader vertex(Graphics::OpenGL::ShaderType::Vertex, vertexSource);
    vertex.compile();

    Graphics::OpenGL::Shader fragment(Graphics::OpenGL::ShaderType::Fragment, fragmentSource);
    fragment.compile();

    return std::make_unique<Graphics::OpenGL::Program>(vertex, fragment);
}
}  // namespace WarriorEngine::Resources::Loaders
