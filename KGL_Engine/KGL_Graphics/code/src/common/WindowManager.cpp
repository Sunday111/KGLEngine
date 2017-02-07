#include <cassert>
#include <KGL_Base/Marco.h>
#include <KGL_Graphics/WindowManager.h>
#include <KGL_Graphics/Render/RenderContext.h>
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

int WindowManager::CreateWindow(Core::Application* app)
{
    assert(m_d != nullptr);
    return m_d->CreateWindow(app);
}

Ptr<RenderContext> WindowManager::CreateRenderContext()
{
    assert(m_d != nullptr);
    return m_d->CreateRenderContext();
}

} }