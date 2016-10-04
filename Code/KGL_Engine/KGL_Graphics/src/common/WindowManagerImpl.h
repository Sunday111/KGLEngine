#ifndef KGL_GRAPHICS_WINDOW_MANAGER_IMPL_H_INCLUDED
#define KGL_GRAPHICS_WINDOW_MANAGER_IMPL_H_INCLUDED

#include "KGL_Graphics/WindowManager.h"
#include <set>

namespace KGL { namespace Graphics {

class WindowImpl;

class WindowManagerImpl
{
public:
    enum { NoCurrentWindow = -1 };

    explicit WindowManagerImpl();
    ~WindowManagerImpl();

    void OnCreateWindow(WindowImpl* wnd);

    void OnDestroyWindow(WindowImpl* wnd);

    void SetCurrentWindow(int windowId);

    void Update();

    int GetCurrentWindowId() const
    {
        return m_currentWindowId;
    }

    int GenerateWindowId()
    {
        return m_nextWindowId++;
    }

private:
    int m_nextWindowId;
    int m_currentWindowId;
    std::set<WindowImpl*> m_windows;
};

} }

#endif /* KGL_GRAPHICS_WINDOW_MANAGER_IMPL_H_INCLUDED */