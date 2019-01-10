#ifndef WARRIOR_ENGINE_ENTRYPOINT_H
#define WARRIOR_ENGINE_ENTRYPOINT_H

#include "Engine/Logging/Logging.h"
#include <memory>

namespace WarriorEngine
{
class Application;
extern Application* createApplication();
}  // namespace WarriorEngine

int main(int argc, char** argv)
{
    using WarriorEngine::Application;
    using WarriorEngine::createApplication;

    WE_ENGINE_INFO("Engine initialization begin");

    std::unique_ptr<Application> app(createApplication());
    app->initialize();

    WE_ENGINE_INFO("Engine initialization end");

    app->run();
}

#endif