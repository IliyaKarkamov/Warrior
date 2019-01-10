#ifndef WARRIOR_ENGINE_INPUT_RAWINPUT_H
#define WARRIOR_ENGINE_INPUT_RAWINPUT_H

#include "Engine/EngineAPI.h"
#include "Engine/Input/enums/RawInputType.h"

namespace WarriorEngine::Input
{
class WE_API RawInput
{
    RawInputType type_;
    int value_;

public:
    RawInput(const RawInputType type, const int value) noexcept;

    bool operator==(const RawInput& other) const noexcept;
    bool operator<(const RawInput& other) const noexcept;

    RawInput(const RawInput&) = default;
    RawInput& operator=(const RawInput&) = default;
    RawInput(RawInput&&) = default;
    RawInput& operator=(RawInput&&) = default;

    RawInputType getType() const noexcept { return type_; }
    int getValue() const noexcept { return value_; }
    int toInt() const noexcept;
};
}  // namespace WarriorEngine::Input

#endif