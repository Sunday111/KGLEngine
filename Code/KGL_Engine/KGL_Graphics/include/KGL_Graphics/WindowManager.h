#ifndef KGL_GRAPHICS_WINDOW_MANAGER_H_INCLUDED
#define KGL_GRAPHICS_WINDOW_MANAGER_H_INCLUDED

#include "KGL_Graphics/Common.h"

namespace KGL { namespace Graphics {

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

private:
    int m_nextWindowId;
    WindowManagerImpl* m_d;
};

} }

#endif /*KGL_GRAPHICS_WINDOW_MANAGER_H_INCLUDED*/