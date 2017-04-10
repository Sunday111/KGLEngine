#pragma once

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "KGL_Base/EnumFlags.h"

namespace KGL { namespace Graphics {

enum class WindowHint
{
    Empty = 0,
    Resizable = 0x1,
    Visible = 0x2,
    Decorated = 0x4,
    Focused = 0x8,
    AutoIconify = 0x10,
    Floating = 0x20
};

KGL_ENUM_FLAG_OPERATORS(WindowHint)

void SetHints(WindowHint hints);
GLFWwindow* CreateWindow(WindowHint hints, int width, int height, GLFWwindow* share, const char* title);

} }