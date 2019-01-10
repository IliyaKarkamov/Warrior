#ifndef WARRIOR_ENGINE_INPUT_INPUTLISTENER_H
#define WARRIOR_ENGINE_INPUT_INPUTLISTENER_H

#include "Engine/EngineAPI.h"
#include "Engine/Input/RawInput.h"
#include "Engine/Input/MappedInput.h"
#include "Engine/Input/ValueNormalizer.h"
#include <functional>
#include <map>

namespace WarriorEngine::Input
{
using OnListenerDispatch = std::function<void(const MappedInput&, const CursorPosition&)>;

struct RangeInput
{
    int range{};
    std::shared_ptr<ValueNormalizer> pNormalizer{nullptr};
};

class WE_API InputListener
{
    std::map<RawInput, int> actions_;
    std::map<RawInput, int> states_;
    std::map<RawInput, RangeInput> ranges_;

    OnListenerDispatch onDispatch_;

public:
    InputListener(std::map<RawInput, int> actions,
                  std::map<RawInput, int> states,
                  std::map<RawInput, RangeInput> ranges);

    InputListener(const InputListener&) = default;
    InputListener& operator=(const InputListener&) = default;
    InputListener(InputListener&&) = default;
    InputListener& operator=(InputListener&&) = default;

    bool hasAction(const RawInput& input, int& action) const;
    bool hasState(const RawInput& input, int& state) const;
    bool hasRange(const RawInput& input, int& range, ValueNormalizer*& normalizer) const;

    void setDispatchCallback(OnListenerDispatch callback);
    void onDispatch(const MappedInput& mappedInput, const CursorPosition& cursorPosition) const;
};
}  // namespace WarriorEngine::Input

#endif