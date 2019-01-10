#include "Engine/Logging/Logger.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "Engine/Core.h"

#define LOG_BUFFER_SIZE 1024
#define FILL_BUFFER                                                                                          \
    char buffer[LOG_BUFFER_SIZE];                                                                            \
    va_list args;                                                                                            \
    va_start(args, format);                                                                                  \
    vsnprintf(buffer, LOG_BUFFER_SIZE, format, args);                                                        \
    va_end(args);

namespace WarriorEngine::Logging
{
namespace detail
{
struct LoggerImpl
{
    std::shared_ptr<spdlog::logger> pLogger;
};
}  // namespace detail

Logger::Logger(const std::string& name) : pImpl_(std::make_shared<detail::LoggerImpl>())
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    pImpl_->pLogger = spdlog::stdout_color_mt(name);
    pImpl_->pLogger->set_level(spdlog::level::trace);
}

void Logger::trace(const char* const format, ...) const
{
    ASSERT(pImpl_->pLogger != nullptr);

    FILL_BUFFER
    pImpl_->pLogger->trace(buffer);
}

void Logger::debug(const char* const format, ...) const
{
    ASSERT(pImpl_->pLogger != nullptr);

    FILL_BUFFER
    pImpl_->pLogger->debug(buffer);
}

void Logger::info(const char* const format, ...) const
{
    ASSERT(pImpl_->pLogger != nullptr);

    FILL_BUFFER
    pImpl_->pLogger->info(buffer);
}

void Logger::warn(const char* const format, ...) const
{
    ASSERT(pImpl_->pLogger != nullptr);

    FILL_BUFFER
    pImpl_->pLogger->warn(buffer);
}

void Logger::error(const char* const format, ...) const
{
    ASSERT(pImpl_->pLogger != nullptr);

    FILL_BUFFER
    pImpl_->pLogger->error(buffer);
}

void Logger::critical(const char* const format, ...) const
{
    ASSERT(pImpl_->pLogger != nullptr);

    FILL_BUFFER
    pImpl_->pLogger->critical(buffer);
}

}  // namespace WarriorEngine::Logging