#ifndef KGL_GRAPHICS_MONITOR_IMPL_H_INCLUDED
#define KGL_GRAPHICS_MONITOR_IMPL_H_INCLUDED

#include <KGL_Graphics\Monitor.h>

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

namespace KGL { namespace Graphics {

class Monitor::Impl
{
public:
    explicit Impl(GLFWmonitor* pm) :
        monitor(pm)
    {
        assert(pm != nullptr);
    }

private:
    GLFWmonitor* monitor;
};

} }

#endif