#ifndef KGL_GRAPHICS_WINDOW_MANAGER_IMPL_H_INCLUDED
#define KGL_GRAPHICS_WINDOW_MANAGER_IMPL_H_INCLUDED

#include "KGL_Graphics/WindowManager.h"
#include <set>

namespace KGL { namespace Graphics {

class WindowImpl;

class WindowManagerImpl
{
public:
    explicit WindowManagerImpl() = default;

    void OnCreateWindow(WindowImpl* wnd)
    {
        m_windows.insert(wnd);
    }

    void OnDestroyWindow(WindowImpl* wnd)
    {
        m_windows.erase(wnd);
    }

private:
    std::set<WindowImpl*> m_windows;
};

} }

#endif /* KGL_GRAPHICS_WINDOW_MANAGER_IMPL_H_INCLUDED */