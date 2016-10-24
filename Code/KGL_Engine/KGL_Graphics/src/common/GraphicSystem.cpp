#include <GraphicSystem.h>
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

DEFINE_SUPPORT_RTTI(GraphicSystem, Graphics::Object)

GraphicSystem::GraphicSystem()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glewExperimental = GL_TRUE;
}

GraphicSystem::~GraphicSystem()
{
    glfwTerminate();
}

bool GraphicSystem::Update()
{
    return m_windowManager.GetImpl()->Update();
}

void GraphicSystem::AddShaderProgram(std::unique_ptr<IShaderProgram> shaderProgram)
{
    m_shaderPrograms.push_back(std::move(shaderProgram));
}

} }