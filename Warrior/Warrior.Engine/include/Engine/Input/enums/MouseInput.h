#ifndef WARRIOR_ENGINE_INPUT_ENUMS_MOUSEINPUT_H
#define WARRIOR_ENGINE_INPUT_ENUMS_MOUSEINPUT_H

namespace WarriorEngine::Input
{
enum class MouseInputAxis
{
    MouseAxisX,
    MouseAxisY
};

enum class MouseScroll
{
    X,
    Y
};

enum class MouseInputButton
{
    MouseButton1 = 0,
    MouseButton2 = 1,
    MouseButton3 = 2,
    MouseButton4 = 3,
    MouseButton5 = 4,
    MouseButton6 = 5,
    MouseButton7 = 6,
    MouseButton8 = 7,
    MouseButtonLeft = 0,
    MouseButtonRight = 1,
    MouseButtonMiddle = 2
};
}  // namespace WarriorEngine::Input

#endif