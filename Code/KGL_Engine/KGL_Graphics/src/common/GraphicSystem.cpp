#include <KGL_Graphics/GraphicSystem.h>
#include <KGL_Graphics/MonitorManager.h>
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

DEFINE_CLASS_RTTI(KGL::Graphics::GraphicSystem, KGL::Core::System)

namespace KGL { namespace Graphics {

class GraphicSystem::Impl
{
public:
	~Impl()
	{
		glfwTerminate();
	}

	WindowManager m_windowManager;
    MonitorManager m_monitorManager;
	std::vector<Ptr<ShaderProgram>> m_shaderPrograms;
};

GraphicSystem::GraphicSystem()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glewExperimental = GL_TRUE;

    m_d = new Impl;
}

GraphicSystem::~GraphicSystem()
{
    SAFE_DELETE(m_d);
}

bool GraphicSystem::Update()
{
	assert(m_d != nullptr);
    return m_d->m_windowManager.GetImpl()->Update();
}

void GraphicSystem::AddShaderProgram(const Ptr<ShaderProgram>& shaderProgram)
{
	assert(m_d != nullptr);
	m_d->m_shaderPrograms.push_back(shaderProgram);
}

WindowManager* GraphicSystem::GetWindowManager()
{
	assert(m_d != nullptr);
	return &m_d->m_windowManager;
}

} }