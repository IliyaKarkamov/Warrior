#include "Engine/Input/InputListener.h"
#include "Engine/Core.h"
#include "Engine/Logging/Logging.h"

namespace WarriorEngine::Input
{
InputListener::InputListener(std::map<RawInput, int> actions,
                             std::map<RawInput, int> states,
                             std::map<RawInput, RangeInput> ranges)
    : actions_(std::move(actions)), states_(std::move(states)), ranges_(std::move(ranges))
{}

bool InputListener::hasAction(const RawInput& input, int& action) const
{
    const auto cit = actions_.find(input);

    if (cit != actions_.end())
    {
        action = cit->second;
        return true;
    }

    return false;
}

bool InputListener::hasState(const RawInput& input, int& state) const
{
    const auto cit = states_.find(input);

    if (cit != states_.end())
    {
        state = cit->second;
        return true;
    }

    return false;
}

bool InputListener::hasRange(const RawInput& input, int& range, ValueNormalizer*& normalizer) const
{
    const auto cit = ranges_.find(input);

    if (cit != ranges_.end())
    {
        auto& rangeInput = cit->second;

        range = rangeInput.range;

        ASSERT(rangeInput.pNormalizer != nullptr);

        normalizer = rangeInput.pNormalizer.get();
        return true;
    }

    return false;
}

void InputListener::setDispatchCallback(OnListenerDispatch callback) { onDispatch_ = std::move(callback); }

void InputListener::onDispatch(const MappedInput& mappedInput, const CursorPosition& cursorPosition) const
{
    if (onDispatch_)
        onDispatch_(mappedInput, cursorPosition);
}
}  // namespace WarriorEngine::Input