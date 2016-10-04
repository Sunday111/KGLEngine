#ifndef KGL_GRAPHICS_WINDOW_IMPL_H_INCLUDED
#define KGL_GRAPHICS_WINDOW_IMPL_H_INCLUDED

#include <assert.h>
#include <set>

struct GLFWwindow;

namespace KGL { namespace Graphics {

class WindowListener;
class WindowManagerImpl;

class WindowImpl
{
public:
    explicit WindowImpl(WindowManagerImpl* mgr);
    ~WindowImpl();

    int GetId() const { return m_id; }
    bool AddListener(WindowListener* listener);
    bool RemoveListener(WindowListener* listener);
    bool ShouldClose() const;
    void Update() const;

    static void PollEvents();

private:
    int m_id;
    GLFWwindow* m_wnd;
    WindowManagerImpl* m_mgr;
    std::set<WindowListener*> m_listeners;
};

} }

#endif /*KGL_GRAPHICS_WINDOW_IMPL_H_INCLUDED*/