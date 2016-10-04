#include "KGL_Graphics/Window.h"
#include "KGL_Graphics/WindowManager.h"
#include "WindowManagerImpl.h"

namespace KGL { namespace Graphics {

WindowManager::WindowManager() :
    m_d(new WindowManagerImpl())
{}

WindowManager::WindowManager(WindowManager&& uref) :
    m_d(uref.m_d)
{
    uref.m_d = nullptr;
}

WindowManager::~WindowManager()
{
    if (m_d != nullptr)
    {
        delete m_d;
    }
}

int WindowManager::GetCurrentWindowId()
{
    return m_d->GetCurrentWindowId();
}

} }