#include "GlfwUtils.h"

namespace KGL { namespace Graphics { namespace {

template<WindowHint targ, int raw>
void CheckHint(WindowHint hints)
{
    glfwWindowHint(
        raw,
        (hints & targ) == WindowHint::Empty ?
        GL_FALSE : GL_TRUE);
}

}

void SetHints(WindowHint hints)
{
    CheckHint<WindowHint::Resizable, GLFW_RESIZABLE>(hints);
    CheckHint<WindowHint::Visible, GLFW_VISIBLE>(hints);
    CheckHint<WindowHint::Decorated, GLFW_DECORATED>(hints);
    CheckHint<WindowHint::Focused, GLFW_FOCUSED>(hints);
    CheckHint<WindowHint::AutoIconify, GLFW_AUTO_ICONIFY>(hints);
    CheckHint<WindowHint::Floating, GLFW_FLOATING>(hints);
}

GLFWwindow* CreateWindow(
    WindowHint hints,
    int width, int height,
    GLFWwindow* share,
    const char* title)
{
    SetHints(hints);

    auto wnd = glfwCreateWindow(width, height, title, nullptr, share);

    glfwDefaultWindowHints();

    return wnd;
}

} }