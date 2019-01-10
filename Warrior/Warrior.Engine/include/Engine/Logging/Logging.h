#ifndef WARRIOR_ENGINE_LOGGING_LOGGING_H
#define WARRIOR_ENGINE_LOGGING_LOGGING_H

#include "Engine/Logging/Logger.h"
#include "Engine/Logging/LoggerRegistry.h"

#define WE_ENGINE_TRACE(...) ::WarriorEngine::Logging::LoggerRegistry::getInstance().getEngineLogger()->trace(__VA_ARGS__)
#define WE_ENGINE_DEBUG(...) ::WarriorEngine::Logging::LoggerRegistry::getInstance().getEngineLogger()->debug(__VA_ARGS__)
#define WE_ENGINE_INFO(...) ::WarriorEngine::Logging::LoggerRegistry::getInstance().getEngineLogger()->info(__VA_ARGS__)
#define WE_ENGINE_WARN(...) ::WarriorEngine::Logging::LoggerRegistry::getInstance().getEngineLogger()->warn(__VA_ARGS__)
#define WE_ENGINE_ERROR(...) ::WarriorEngine::Logging::LoggerRegistry::getInstance().getEngineLogger()->error(__VA_ARGS__)
#define WE_ENGINE_CRITICAL(...) ::WarriorEngine::Logging::LoggerRegistry::getInstance().getEngineLogger()->critical(__VA_ARGS__)

#define WE_TRACE(...) ::WarriorEngine::Logging::LoggerRegistry::getInstance().getClientLogger()->trace(__VA_ARGS__)
#define WE_DEBUG(...) ::WarriorEngine::Logging::LoggerRegistry::getInstance().getClientLogger()->debug(__VA_ARGS__)
#define WE_INFO(...) ::WarriorEngine::Logging::LoggerRegistry::getInstance().getClientLogger()->info(__VA_ARGS__)
#define WE_WARN(...) ::WarriorEngine::Logging::LoggerRegistry::getInstance().getClientLogger()->warn(__VA_ARGS__)
#define WE_ERROR(...) ::WarriorEngine::Logging::LoggerRegistry::getInstance().getClientLogger()->error(__VA_ARGS__)
#define WE_CRITICAL(...) ::WarriorEngine::Logging::LoggerRegistry::getInstance().getClientLogger()->critical(__VA_ARGS__)

#endif