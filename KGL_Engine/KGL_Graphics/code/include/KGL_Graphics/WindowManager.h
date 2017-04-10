#ifndef KGL_GRAPHICS_WINDOW_MANAGER_H_INCLUDED
#define KGL_GRAPHICS_WINDOW_MANAGER_H_INCLUDED

#include <KGL_Base/Ptr.h>
#include <KGL_Graphics/Common.h>

namespace KGL { namespace Core {

class Application;

} }

namespace KGL { namespace Graphics {

class Application;
class GraphicSystem;
class RenderContext;
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

    int CreateWindow(Core::Application* app, int sharedWindowContext = -1);
    int CreateWindow(Core::Application* app, Ptr<RenderContext> renderContext = nullptr);
    
    Ptr<RenderContext> CreateRenderContext();

private:
    int m_nextWindowId;
    WindowManagerImpl* m_d;
};

} }

#endif