#include "Engine/Logging/LoggerRegistry.h"
#include "Engine/Core.h"

namespace WarriorEngine::Logging
{
LoggerRegistry& LoggerRegistry::getInstance()
{
    static LoggerRegistry registry;
    return registry;
}

Logger* LoggerRegistry::getEngineLogger() const
{
    ASSERT(pEngineLogger_ != nullptr);
    return pEngineLogger_.get();
}

Logger* LoggerRegistry::getClientLogger() const
{
    ASSERT(pEngineLogger_ != nullptr);
    return pClientLogger_.get();
}

LoggerRegistry::LoggerRegistry()
{
    pEngineLogger_ = std::make_unique<Logger>("WARRIOR_ENGINE");
    pClientLogger_ = std::make_unique<Logger>("APPLICATION");
}
}  // namespace WarriorEngine::Logging
