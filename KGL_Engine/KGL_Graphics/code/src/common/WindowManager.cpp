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
    SafeDelete(m_d);
}

int WindowManager::GetCurrentWindowId()
{
    return m_d->GetCurrentWindowId();
}

int WindowManager::CreateWindow(Core::Application* app, int sharedWindowContext)
{
    assert(m_d != nullptr);
    return m_d->CreateWindow(app, sharedWindowContext);
}

int WindowManager::CreateWindow(Core::Application* app, Ptr<RenderContext> renderContext)
{
    assert(m_d != nullptr);
    return m_d->CreateWindow(app, renderContext);
}

Ptr<RenderContext> WindowManager::CreateRenderContext()
{
    assert(m_d != nullptr);
    return m_d->CreateRenderContext();
}

} }