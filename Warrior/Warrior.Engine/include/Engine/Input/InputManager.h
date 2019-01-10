#ifndef WARRIOR_ENGINE_INPUT_INPUTMANAGER_H
#define WARRIOR_ENGINE_INPUT_INPUTMANAGER_H

#include "Engine/EngineAPI.h"
#include "Engine/Input/InputListener.h"
#include <map>

namespace WarriorEngine::Input
{
class WE_API InputManager
{
    struct InputBindings
    {
        InputListener* pListener = nullptr;
        std::unique_ptr<MappedInput> pMappedInput = nullptr;

        explicit InputBindings(InputListener* listener, std::unique_ptr<MappedInput> mappedInput);
    };

    std::map<int, InputBindings> bindings_;
    std::map<RawInput, bool> previouslyPressed_;
    CursorPosition cursorPosition_{};

public:
    InputManager() = default;

    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    void addListener(const int priority, InputListener* pListener);

    void processButton(const RawInput& input, const bool pressed);
    void processMove(const RawInput& input, const float value);
    void processScroll(const RawInput& input, const float value);

    void dispatch();
};
}  // namespace WarriorEngine::Input

#endif