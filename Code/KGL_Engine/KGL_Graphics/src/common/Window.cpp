#include <cassert>
#include <KGL_Graphics/Window.h>
#include <KGL_Graphics/WindowManager.h>
#include <set>
#include "WindowImpl.h"
#include "WindowManagerImpl.h"

namespace KGL { namespace Graphics {

Window::Window(WindowManager* mgr) :
    m_d(new WindowImpl(mgr->GetImpl()))
{}

Window::Window(Window&& uref) :
    m_d(uref.m_d)
{
    uref.m_d = nullptr;
}

Window::~Window()
{
    if (m_d != nullptr)
    {
        delete m_d;
    }
}

bool Window::AddListener(WindowListener* listener)
{
    if (m_d == nullptr)
    {
        assert(!"Attempt to call object with empty definition!");
        return false;
    }

    return m_d->AddListener(listener);
}

bool Window::RemoveListener(WindowListener* listener)
{
    if (m_d == nullptr)
    {
        assert(!"Attempt to call object with empty definition!");
        return false;
    }

    return m_d->RemoveListener(listener);
}

} }