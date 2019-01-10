#include "Engine/Input/ValueNormalizer.h"
#include "Engine/Core.h"

namespace WarriorEngine::Input
{
ValueNormalizer::ValueNormalizer(const int minimumInput,
                                 const int maximumInput,
                                 const int minimumOutput,
                                 const int maximumOutput)
    : minimumInput_(minimumInput),
      maximumInput_(maximumInput),
      minimumOutput_(minimumOutput),
      maximumOutput_(maximumOutput)
{}

float ValueNormalizer::normalize(const float value) const
{
    ASSERT(maximumOutput_ != minimumOutput_);

    return minimumOutput_ + (value - minimumInput_) * (maximumOutput_ - minimumOutput_) /
                                static_cast<float>(maximumInput_ - minimumInput_);
}
}  // namespace WarriorEngine::Input
