#ifndef WARRIOR_ENGINE_GRAPHICS_OPENGL_RENDERER_H
#define WARRIOR_ENGINE_GRAPHICS_OPENGL_RENDERER_H

#include "Engine/EngineAPI.h"
#include "Engine/Graphics/OpenGL/enums/Capability.h"
#include "Engine/Graphics/OpenGL/enums/PrimitiveType.h"
#include "Engine/Graphics/OpenGL/enums/BufferType.h"
#include "Engine/Graphics/OpenGL/enums/BlendingFactor.h"
#include "Engine/Graphics/OpenGL/enums/BlendingEquation.h"
#include "Engine/Graphics/OpenGL/enums/DataType.h"
#include "Engine/Graphics/OpenGL/enums/CullFaceMode.h"
#include "Engine/Graphics/OpenGL/enums/DepthFunc.h"
#include "Engine/Graphics/OpenGL/glm/vec4.hpp"

namespace WarriorEngine::Graphics::OpenGL
{
class WE_API Renderer
{
public:
    static void viewport(const int x, const int y, const int width, const int height);
    static void wireframe(const bool isOn);

    static void enable(const Capability capability);
    static void disable(const Capability capability);

    static void cullFace(const CullFaceMode mode);

    static void depthMask(const bool enable);
    static void depthFunc(const DepthFunc func);

    static void blendFunc(const BlendingFactor sfactor, const BlendingFactor dfactor);
    static void blendEquation(const BlendingEquation mode);

    static void clearColor(const glm::vec4& color);
    static void clear(const BufferType buffers = BufferType::Color | BufferType::Depth);

    static void drawArrays(const PrimitiveType mode, const int offset, const int vertices);
    static void drawElements(const PrimitiveType mode,
                             const int offset,
                             const int count,
                             const DataType type);
};
}  // namespace WarriorEngine::Graphics::OpenGL

#endif
