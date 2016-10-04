#ifndef KGL_GRAPHICS_WINDOW_IMPL_H_INCLUDED
#define KGL_GRAPHICS_WINDOW_IMPL_H_INCLUDED

#include <assert.h>
#include <set>

namespace KGL { namespace Graphics {

class WindowListener;
class WindowManagerImpl;

class WindowImpl
{
public:
    explicit WindowImpl(WindowManagerImpl* mgr);
    ~WindowImpl();

    bool AddListener(WindowListener* listener);
    bool RemoveListener(WindowListener* listener);

private:
    WindowManagerImpl* m_mgr;
    std::set<WindowListener*> m_listeners;
};

} }

#endif /*KGL_GRAPHICS_WINDOW_IMPL_H_INCLUDED*/