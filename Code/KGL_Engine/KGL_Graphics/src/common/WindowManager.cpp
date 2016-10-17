#include <cassert>
#include <KGL_Base/Marco.h>
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
    SAFE_DELETE(m_d);
}

int WindowManager::GetCurrentWindowId()
{
    return m_d->GetCurrentWindowId();
}

int WindowManager::CreateWindow()
{
    if (m_d == nullptr)
    {
        assert(false);
        return -1;
    }

    return m_d->CreateWindow();
}

} }