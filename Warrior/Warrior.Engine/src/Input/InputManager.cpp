#include "Engine/Input/InputManager.h"
#include "Engine/Input/enums/MouseInput.h"

namespace WarriorEngine::Input
{
InputManager::InputBindings::InputBindings(InputListener* listener, std::unique_ptr<MappedInput> mappedInput)
    : pListener(listener), pMappedInput(std::move(mappedInput))
{}

void InputManager::addListener(const int priority, InputListener* pListener)
{
    InputBindings binding(pListener, std::make_unique<MappedInput>());
    bindings_.emplace(priority, std::move(binding));
}

void InputManager::processButton(const RawInput& input, const bool pressed)
{
    if (pressed)
    {
        if (!previouslyPressed_[input])
            for (auto&& [k, binding] : bindings_)
                if (int action; binding.pListener->hasAction(input, action))
                {
                    binding.pMappedInput->actions.insert(action);
                    previouslyPressed_[input] = true;
                    return;
                }

        for (auto&& [k, binding] : bindings_)
            if (int state; binding.pListener->hasState(input, state))
            {
                binding.pMappedInput->states.insert(state);
                previouslyPressed_[input] = true;
                return;
            }
    }

    for (auto&& [k, binding] : bindings_)
        if (int state; binding.pListener->hasState(input, state))
            binding.pMappedInput->states.erase(state);

    previouslyPressed_[input] = false;
}

void InputManager::processMove(const RawInput& input, const float value)
{
    static auto lastX = 0;
    static auto lastY = 0;

    auto rangeValue = 0;

    if (static_cast<MouseInputAxis>(input.getValue()) == MouseInputAxis::MouseAxisX)
    {
        rangeValue = value - lastX;
        lastX = value;
        cursorPosition_.x = value;
    }
    else
    {
        rangeValue = value - lastY;
        lastY = value;
        cursorPosition_.y = value;
    }

    for (auto&& [k, binding] : bindings_)
    {
        int range;
        ValueNormalizer* normalizer;

        if (binding.pListener->hasRange(input, range, normalizer))
            binding.pMappedInput->ranges.insert(std::make_pair(range, normalizer->normalize(rangeValue)));
    }
}

void InputManager::processScroll(const RawInput& input, const float value)
{
    for (auto&& [k, binding] : bindings_)
    {
        int range;
        ValueNormalizer* normalizer;

        if (binding.pListener->hasRange(input, range, normalizer))
            binding.pMappedInput->ranges.insert(std::make_pair(range, normalizer->normalize(value)));
    }
}

void InputManager::dispatch()
{
    for (auto&& [k, binding] : bindings_)
    {
        binding.pListener->onDispatch(*binding.pMappedInput, cursorPosition_);
        binding.pMappedInput->clear();
    }
}
}  // namespace WarriorEngine::Input
