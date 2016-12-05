#ifndef KGL_GRAPHICS_CONTEXT_H_INCLUDED
#define KGL_GRAPHICS_CONTEXT_H_INCLUDED

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

namespace KGL { namespace Graphics {

class Context
{
public:
    explicit Context(int width, int height, const char* title, );

private:
    GLFWwindow* m_wnd;
};

} }

#endif