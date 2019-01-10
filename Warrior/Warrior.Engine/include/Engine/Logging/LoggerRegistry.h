#ifndef WARRIOR_ENGINE_LOGGING_LOGGERREGISTRY_H
#define WARRIOR_ENGINE_LOGGING_LOGGERREGISTRY_H

#include "Engine/EngineAPI.h"
#include "Engine/Logging/Logger.h"
#include <memory>

namespace WarriorEngine::Logging
{
class WE_API LoggerRegistry
{
    std::unique_ptr<Logger> pEngineLogger_;
    std::unique_ptr<Logger> pClientLogger_;

public:
    static LoggerRegistry& getInstance();

    Logger* getEngineLogger() const;
    Logger* getClientLogger() const;

    LoggerRegistry(const LoggerRegistry&) = delete;
    LoggerRegistry& operator=(const LoggerRegistry&) = delete;

private:
    LoggerRegistry();
};
}  // namespace WarriorEngine::Logging

#endif