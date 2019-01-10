#ifndef WARRIOR_ENGINE_LOGGING_LOGGER_H
#define WARRIOR_ENGINE_LOGGING_LOGGER_H

#include "Engine/EngineAPI.h"
#include <memory>
#include <string>

namespace WarriorEngine::Logging
{
namespace detail
{
struct LoggerImpl;
}

class WE_API Logger
{
    std::shared_ptr<detail::LoggerImpl> pImpl_;

public:
    Logger(const std::string& name);

    void trace(const char* const format, ...) const;
    void debug(const char* const format, ...) const;
    void info(const char* const format, ...) const;
    void warn(const char* const format, ...) const;
    void error(const char* const format, ...) const;
    void critical(const char* const format, ...) const;
};

}  // namespace WarriorEngine::Logging

#endif