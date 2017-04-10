#pragma once

#include "GlfwUtils.h"

namespace KGL { namespace Graphics {

class RenderContextImpl
{
public:
    RenderContextImpl(int id_) :
        id(id_),
        // In fact render context is an empty window
        wnd(CreateWindow(WindowHint::Empty, 100, 100, nullptr, "KGL Render Context"))
    {
    }

    ~RenderContextImpl()
    {
        glfwDestroyWindow(wnd);
    }

    int id;
    GLFWwindow* wnd;
};

} }