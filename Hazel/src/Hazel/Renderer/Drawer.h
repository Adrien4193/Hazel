#pragma once

#include "glm/glm.hpp"

#include "VertexArray.h"

namespace Hazel
{
    class Drawer
    {
    public:
        virtual ~Drawer() = default;

        virtual void SwapBuffers() = 0;
        virtual void SetViewport(int width, int height) = 0;
        virtual void SetClearColor(const glm::vec4 &color) = 0;
        virtual void Clear() = 0;
        virtual void DrawIndexed(const SharedPtr<VertexArray> &vertexArray) = 0;
    };
}