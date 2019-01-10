#include "Engine/Input/RawInput.h"

namespace WarriorEngine::Input
{
RawInput::RawInput(const RawInputType type, const int value) noexcept : type_(type), value_(value) {}

bool RawInput::operator==(const RawInput& other) const noexcept
{
    return type_ == other.type_ && value_ == other.value_;
}

bool RawInput::operator<(const RawInput& other) const noexcept
{
    return toInt() < other.toInt();
}

int RawInput::toInt() const noexcept { return static_cast<int>(type_) * 1000 + value_; }
}  // namespace WarriorEngine::Input
