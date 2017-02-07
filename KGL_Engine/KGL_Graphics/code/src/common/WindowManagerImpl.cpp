#include <algorithm>
#include "WindowImpl.h"
#include "WindowManagerImpl.h"
#include <KGL_Graphics/Render/RenderContext.h>

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

namespace KGL { namespace Graphics {

WindowManagerImpl::WindowManagerImpl() :
    m_nextWindowId(0),
    m_currentWindowId(NoCurrentWindow)
{}

WindowManagerImpl::~WindowManagerImpl()
{
    m_windows.clear();
    glfwTerminate();
}

void WindowManagerImpl::SetCurrentWindow(int windowId)
{
    assert(windowId != -1);
    m_currentWindowId = windowId;
}

bool WindowManagerImpl::Update()
{
    if (m_windows.empty())
    {
        return false;
    }

    m_windows.erase(
        std::remove_if(m_windows.begin(), m_windows.end(),
            [](const std::unique_ptr<WindowImpl>& wnd)
            {
                if(wnd->ShouldClose())
                {
                    return true;
                }

                wnd->Update();
                return false;
            }),
        m_windows.end());

    /* Check if any events have been activiated (key pressed, mouse moved etc.)
     * and call corresponding response functions */
    glfwPollEvents();

    return true;
}

int WindowManagerImpl::CreateWindow(Core::Application* app, int windowSharedContext)
{
    Ptr<RenderContext> ctx;

    if(windowSharedContext == -1)
    {
        auto wnd = GetWindow(windowSharedContext);

        if(wnd == nullptr)
        {
            return -1;
        }

        ctx = wnd->GetContext();
    }
    else
    {
        ctx = CreateRenderContext();
    }

    m_windows.push_back(std::make_unique<WindowImpl>(this, app, ctx));
    return m_windows.back()->GetId();
}

KGL::Ptr<RenderContext> WindowManagerImpl::CreateRenderContext()
{
    return new RenderContext(GenerateRenderContextId());
}

WindowImpl* WindowManagerImpl::GetWindow(int id)
{
    for(auto& wnd : m_windows)
    {
        if (wnd->GetId() == id)
        {
            return wnd.get();
        }
    }

    return nullptr;
}

} }