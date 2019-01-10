#ifndef WARRIOR_ENGINE_APPLICATION_H
#define WARRIOR_ENGINE_APPLICATION_H

#include "Engine/EngineAPI.h"
#include "Engine/Window.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Resources/ResourceManager.h"

namespace WarriorEngine
{
class WE_API Application
{
    std::unique_ptr<Window> pWindow_ = nullptr;
    std::unique_ptr<Input::InputManager> pInputManager_ = nullptr;
    std::unique_ptr<Resources::ResourceManager> pResourceManager_ = nullptr;

    float fps_ = 0.f;

public:
    Application();
    virtual ~Application() = default;

    void run();

    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    Window& getWindow() const;
    Input::InputManager& getInputManager() const;
    Resources::ResourceManager& getResourceManager() const;

    float getFps() const noexcept { return fps_; }
};

Application* createApplication();
}  // namespace WarriorEngine

#endif