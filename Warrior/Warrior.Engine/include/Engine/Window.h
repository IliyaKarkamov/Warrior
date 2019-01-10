#ifndef WARRIOR_ENGINE_WINDOW_H
#define WARRIOR_ENGINE_WINDOW_H

#include "Engine/EngineAPI.h"
#include "Engine/Input/InputManager.h"
#include <memory>
#include <string>

namespace WarriorEngine
{
namespace detail
{
struct WindowImpl;
}

class WE_API Window
{
    std::shared_ptr<detail::WindowImpl> pImpl_;

public:
    Window(const int width, const int height, const std::string& title);
    ~Window();

    void setInputManager(Input::InputManager* pInputManager) const;

    bool isAlive() const;
    
    void vSync(const bool enable) const;
    bool isVSync() const;

    void hide() const;
    void show() const;
    void focus() const;

    int getWidth() const noexcept;
    int getHeight() const noexcept;
    float getAspectRatio() const noexcept;

    void fullscreen() const;

    void pollEvents() const;
    void draw() const;
};
}  // namespace WarriorEngine

#endif