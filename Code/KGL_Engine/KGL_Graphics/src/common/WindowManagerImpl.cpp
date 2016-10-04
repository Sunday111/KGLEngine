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
    for (auto wnd : m_windows)
    {
        delete wnd;
    }

    glfwTerminate();
}

void WindowManagerImpl::OnCreateWindow(WindowImpl* wnd)
{
    m_windows.insert(wnd);
}

void WindowManagerImpl::OnDestroyWindow(WindowImpl* wnd)
{
    m_windows.erase(wnd);
}

void WindowManagerImpl::SetCurrentWindow(int windowId)
{
    assert(windowId != -1);
    m_currentWindowId = windowId;
}

void WindowManagerImpl::Update()
{
    for (WindowImpl* wnd : m_windows)
    {
        wnd->Update();
        glfwPollEvents();
    }

}

} }