#include "WindowManagerImpl.h"
#include "WindowImpl.h"

namespace KGL { namespace Graphics {

WindowImpl::WindowImpl(WindowManagerImpl* mgr) :
    m_mgr(mgr)
{
    assert(mgr != nullptr);
    m_mgr->OnCreateWindow(this);
}

WindowImpl::~WindowImpl()
{
    m_mgr->OnDestroyWindow(this);
}

bool WindowImpl::AddListener(WindowListener* listener)
{
    return m_listeners.insert(listener).second;
}

bool WindowImpl::RemoveListener(WindowListener* listener)
{
    return m_listeners.erase(listener) > 0;
}

} }