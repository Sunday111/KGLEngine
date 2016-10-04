#include <KGL_Graphics/GraphicSystem.h>
#include <iostream>
#include <cassert>

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

        GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
        if (window == nullptr)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            assert(false);
            return;
        }
        glfwMakeContextCurrent(window);

        const auto glewInitResult = glewInit();
        if (glewInitResult != GLEW_OK)
        {
            std::cerr << "Failed to initialize GLEW:"
                << glewGetErrorString(glewInitResult) << std::endl;
            assert(false);
        }
    }
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

} }