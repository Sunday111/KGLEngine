#ifndef KGL_GRAPHICS_WINDOW_MANAGER_IMPL_H_INCLUDED
#define KGL_GRAPHICS_WINDOW_MANAGER_IMPL_H_INCLUDED

#include <KGL_Base/Ptr.h>
#include <KGL_Graphics/WindowManager.h>
#include <memory>
#include <vector>

namespace KGL { namespace Core {

class Application;

} }

namespace KGL { namespace Graphics {

class WindowImpl;
class RenderContext;

class WindowManagerImpl
{
public:
    enum { NoCurrentWindow = -1 };

    explicit WindowManagerImpl();
    ~WindowManagerImpl();

    void SetCurrentWindow(int windowId);

    bool Update();

    int GetCurrentWindowId() const
    {
        return m_currentWindowId;
    }

    int GenerateWindowId()
    {
        return m_nextWindowId++;
    }

    int CreateWindow(Core::Application* app, int windowSharedContext = -1);
    KGL::Ptr<RenderContext> CreateRenderContext();

    size_t GetWindowsCount() const
    {
        return static_cast<int>(m_windows.size());
    }

    WindowImpl* GetWindow(int id);

private:
    int m_nextWindowId;
    int m_currentWindowId;
    std::vector<std::unique_ptr<WindowImpl>> m_windows;
};

} }

#endif