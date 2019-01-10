#ifndef WARRIOR_ENGINE_INPUT_VALUENORMALIZER_H
#define WARRIOR_ENGINE_INPUT_VALUENORMALIZER_H

#include "Engine/EngineAPI.h"

namespace WarriorEngine::Input
{
class WE_API ValueNormalizer
{
    int minimumInput_;
    int maximumInput_;

    int minimumOutput_;
    int maximumOutput_;

public:
    ValueNormalizer() = default;
    ValueNormalizer(ValueNormalizer&&) = default;
    ValueNormalizer& operator=(ValueNormalizer&&) = default;
    ValueNormalizer(const ValueNormalizer&) = delete;
    ValueNormalizer& operator=(const ValueNormalizer&) = delete;

    ValueNormalizer(const int minimumInput,
                    const int maximumInput,
                    const int minimumOutput,
                    const int maximumOutput);

    float normalize(const float value) const;
};
}  // namespace WarriorEngine::Input

#endif