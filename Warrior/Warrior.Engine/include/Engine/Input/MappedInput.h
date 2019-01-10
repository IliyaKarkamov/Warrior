#ifndef WARRIOR_ENGINE_INPUT_MAPPEDINPUT_H
#define WARRIOR_ENGINE_INPUT_MAPPEDINPUT_H

#include "Engine/EngineAPI.h"
#include <set>
#include <map>

namespace WarriorEngine::Input
{
struct CursorPosition
{
    float x, y;
};

struct WE_API MappedInput
{
    std::set<int> actions;
    std::set<int> states;
    std::map<int, float> ranges;

    void clear();  
};
}  // namespace WarriorEngine::Input

#endif