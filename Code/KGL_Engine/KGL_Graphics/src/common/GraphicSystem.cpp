#include <KGL_Graphics/GraphicSystem.h>
#include <KGL_Graphics/WindowManager.h>
#include <iostream>
#include <cassert>
#include "WindowManagerImpl.h"

// GLEW
#ifndef GLEW_STATIC
    #define GLEW_STATIC
#endif
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

namespace KGL { namespace Graphics {

class GraphicSystem::GraphicSystemImpl
{
public:
    explicit GraphicSystemImpl()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        glewExperimental = GL_TRUE;
    }

    WindowManager* GetWindowManager()
    {
        return &m_windowManager;
    }

private:
    WindowManager m_windowManager;
};

GraphicSystem::GraphicSystem() :
    m_d(new GraphicSystemImpl())
{}

GraphicSystem::GraphicSystem(GraphicSystem&& uref) :
    m_d(uref.m_d)
{
    uref.m_d = nullptr;
}

GraphicSystem::~GraphicSystem()
{
    if (m_d != nullptr)
    {
        delete m_d;
        glfwTerminate();
    }
}

bool GraphicSystem::Update()
{
    return m_d->GetWindowManager()->GetImpl()->Update();
}

WindowManager* GraphicSystem::GetWindowManager()
{
    return m_d->GetWindowManager();
}

} }