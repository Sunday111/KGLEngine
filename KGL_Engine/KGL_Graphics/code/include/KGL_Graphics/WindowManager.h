#ifndef KGL_GRAPHICS_WINDOW_MANAGER_H_INCLUDED
#define KGL_GRAPHICS_WINDOW_MANAGER_H_INCLUDED

#include "KGL_Graphics/Common.h"

namespace KGL { namespace Core {

class Application;

} }

namespace KGL { namespace Graphics {

class Application;
class GraphicSystem;
class Window;
class WindowManagerImpl;

class KGL_GRAPHICS_API WindowManager
{
public:

    explicit WindowManager();
    explicit WindowManager(const WindowManager&) = delete;
    explicit WindowManager(WindowManager&& uref);
    ~WindowManager();

    WindowManagerImpl* GetImpl() const { return m_d; }
    int GetCurrentWindowId();

    /* Create window and return it's id */
    int CreateWindow(Core::Application* app);

private:
    int m_nextWindowId;
    WindowManagerImpl* m_d;
};

} }

#endif