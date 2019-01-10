#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_ERRORHANDLER_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_ERRORHANDLER_H

#include "Engine/Core.h"
#include "Engine/Logging/Logging.h"
#include <GL/glew.h>

#define GL_CALL(x)                                                                                           \
    clearErrors();                                                                                           \
    x;                                                                                                       \
    ASSERT(!logCall(#x, __FILE__, __LINE__))

namespace WarriorEngine::Graphics::OpenGL
{
inline void clearErrors()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

inline bool logCall(const char* function, const char* file, const int line)
{
    auto bHasErrors = false;

    while (const auto errorCode = glGetError())
    {
        WE_ENGINE_ERROR("[OpenGL error]: ErrorCode = %u\n Function: %s\nFile: %s,Line: %d",
                        errorCode,
                        function,
                        file,
                        line);

        bHasErrors = true;
    }

    return bHasErrors;
}
}  // namespace WarriorEngine::Graphics::OpenGL

#endif