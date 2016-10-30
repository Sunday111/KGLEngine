#include <KGL_Graphics/GraphicSystem.h>
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

DEFINE_SUPPORT_RTTI(GraphicSystem, Core::System)

class GraphicSystem::Impl
{
public:
	~Impl()
	{
		glfwTerminate();
	}

	WindowManager m_windowManager;
	std::vector<std::unique_ptr<ShaderProgram>> m_shaderPrograms;
};

GraphicSystem::GraphicSystem() :
	m_d(new Impl)
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
	assert(m_d != nullptr);
	delete m_d;
}

bool GraphicSystem::Update()
{
	assert(m_d != nullptr);
    return m_d->m_windowManager.GetImpl()->Update();
}

void GraphicSystem::AddShaderProgram(std::unique_ptr<ShaderProgram> shaderProgram)
{
	assert(m_d != nullptr);
	m_d->m_shaderPrograms.push_back(std::move(shaderProgram));
}

WindowManager* GraphicSystem::GetWindowManager()
{
	assert(m_d != nullptr);
	return &m_d->m_windowManager;
}

} }