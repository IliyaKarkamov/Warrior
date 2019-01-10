#include "Engine/Application.h"
#include "Engine/Core.h"
#include "Engine/Resources/ResourceManager.h"
#include <chrono>

namespace WarriorEngine
{
constexpr float c_msPerUpdate = 0.1f;

Application::Application()
{
    pWindow_ = std::make_unique<Window>(800, 600, "Warrior Engine");
    pInputManager_ = std::make_unique<Input::InputManager>();
    pResourceManager_ = std::make_unique<Resources::ResourceManager>();

    pWindow_->setInputManager(pInputManager_.get());
}

void Application::run()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;

    ASSERT(pWindow_ != nullptr);
    ASSERT(pInputManager_ != nullptr);
    ASSERT(pResourceManager_ != nullptr);

    auto previousTime = high_resolution_clock::now();
    auto lag = 0.f;

    while (pWindow_->isAlive())
    {
        const auto currentTime = high_resolution_clock::now();
        const auto elapsedTime = currentTime - previousTime;
        const auto elapsedMS = duration_cast<duration<float, std::milli>>(elapsedTime).count();

        previousTime = currentTime;
        lag += elapsedMS;

        pWindow_->pollEvents();
        pInputManager_->dispatch();

        for (; lag >= c_msPerUpdate; lag -= c_msPerUpdate)
            update();

        draw();
        pWindow_->draw();
        pResourceManager_->update();

        const auto ftSeconds = elapsedMS / 1000.f;
        fps_ = 1.f / ftSeconds;
    }
}

Window& Application::getWindow() const
{
    ASSERT(pWindow_ != nullptr);
    return *pWindow_;
}

Input::InputManager& Application::getInputManager() const
{
    ASSERT(pInputManager_ != nullptr);
    return *pInputManager_;
}

Resources::ResourceManager& Application::getResourceManager() const
{
    ASSERT(pResourceManager_ != nullptr);
    return *pResourceManager_;
}
}  // namespace WarriorEngine
