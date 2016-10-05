#include <algorithm>
#include "WindowManagerImpl.h"
#include "WindowImpl.h"

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

    glfwPollEvents();
    return true;
}

int WindowManagerImpl::CreateWindow()
{
    m_windows.push_back(std::make_unique<WindowImpl>(this));
    return m_windows.back()->GetId();
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