#include <iostream>
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

WindowImpl::WindowImpl(WindowManagerImpl* mgr) :
    m_mgr(mgr),
    m_wnd(nullptr),
    m_id(-1)
{
    assert(m_mgr != nullptr);

    m_id = m_mgr->GenerateWindowId();
    m_mgr->OnCreateWindow(this);

    m_wnd = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (m_wnd == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        assert(false);
        return;
    }
    glfwMakeContextCurrent(m_wnd);

    const auto glewInitResult = glewInit();
    if (glewInitResult != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW:"
            << glewGetErrorString(glewInitResult) << std::endl;
        assert(false);
    }
}

WindowImpl::~WindowImpl()
{
    m_mgr->OnDestroyWindow(this);

    if (m_wnd != nullptr)
    {
        glfwDestroyWindow(m_wnd);
    }
}

bool WindowImpl::AddListener(WindowListener* listener)
{
    return m_listeners.insert(listener).second;
}

bool WindowImpl::RemoveListener(WindowListener* listener)
{
    return m_listeners.erase(listener) > 0;
}

bool WindowImpl::ShouldClose() const
{
    auto result = glfwWindowShouldClose(m_wnd);
    return result != 0;
}

void WindowImpl::Update() const
{
    glfwMakeContextCurrent(m_wnd);
    m_mgr->SetCurrentWindow(m_id);
    glfwSwapBuffers(m_wnd);  // make this loop through all current windows??
}

void WindowImpl::PollEvents()
{
}

} }