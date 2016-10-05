#include <cassert>
#include <KGL_Graphics/Window.h>
#include <KGL_Graphics/WindowManager.h>
#include <set>
#include "WindowImpl.h"
#include "WindowManagerImpl.h"

namespace KGL { namespace Graphics {


Window::Window() :
    m_id(-1),
    m_mgr(nullptr)
{}

Window::Window(int id, WindowManager* mgr) :
    m_id(id),
    m_mgr(mgr)
{
    assert(m_mgr != nullptr && m_id >= 0);
}

bool Window::AddListener(WindowListener* listener)
{
    assert(m_mgr != nullptr && m_id >= 0);

    auto impl = m_mgr->GetImpl()->GetWindow(m_id);

    if (impl == nullptr)
    {
        return false;
    }

    return impl->AddListener(listener);
}

bool Window::RemoveListener(WindowListener* listener)
{
    assert(m_mgr != nullptr && m_id >= 0);

    auto impl = m_mgr->GetImpl()->GetWindow(m_id);

    if (impl == nullptr)
    {
        return false;
    }

    return impl->RemoveListener(listener);
}

bool Window::ShouldClose() const
{
    assert(m_mgr != nullptr && m_id >= 0);

    auto impl = m_mgr->GetImpl()->GetWindow(m_id);

    if (impl == nullptr)
    {
        return false;
    }

    return impl->ShouldClose();
}

int Window::GetId() const
{
    return m_id;
}

} }