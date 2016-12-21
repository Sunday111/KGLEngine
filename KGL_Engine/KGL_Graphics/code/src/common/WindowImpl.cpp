#include <iostream>
#include <sstream>
#include <KGL_Base/Marco.h>
#include <KGL_Core/Application.h>
#include <KGL_Core/ResourceManager.h>
#include <KGL_Graphics/GraphicSystem.h>
#include <KGL_Graphics/Render/Shaders/ShaderType.h>
#include <KGL_Graphics/Render/Shaders/Shader.h>
#include <KGL_Graphics/Render/Shaders/ShaderProgram.h>
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

namespace
{

template<ShaderType st>
decltype(auto) CreateShader(const char* file)
{
	auto shader = Ptr<Shader<st>>(new Shader<st>());
    assertexpr(shader->Compile(file, nullptr, &std::cout));
    return shader;
}

}

WindowImpl::WindowImpl(WindowManagerImpl* mgr, Core::Application* app) :
    m_mgr(mgr),
    m_wnd(nullptr),
    m_id(-1)
{
    assert(m_mgr != nullptr);

    m_id = m_mgr->GenerateWindowId();

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

	auto resourceMgr = app->GetResouceManager();
	assert(resourceMgr != nullptr);

    std::stringstream stream;

    /* Create shader program instance */
    testShader = std::make_unique<ShaderProgram>();

    {
        stream << "file=\"" << "Data\\Resources\\Shaders\\Vertex\\Simplest.res" << "\";";
        stream << "window=" << m_id << ';';

        auto vs = resourceMgr->LoadResourceAs<Shader<ShaderType::Vertex>>(stream.str().data());

        assertexpr(testShader->AddShader(vs, false));
    }

    stream.str(std::string());

    {
        stream << "file=\"" << "Data\\Resources\\Shaders\\Fragment\\Simplest.res" << "\";";
        stream << "window=" << m_id << ';';
        auto fs = resourceMgr->LoadResourceAs<Shader<ShaderType::Fragment>>(stream.str().data());
        assertexpr(testShader->AddShader(fs, false));
    }

	/* Link shaders into shader prgram */
	assertexpr(testShader->Link(&std::cout));

    GLfloat vertices[] = {
        0.5f,  0.5f, 0.0f,  // Top Right
        0.5f, -0.5f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f,  // Bottom Left
        -0.5f,  0.5f, 0.0f   // Top Left 
    };

    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3,  // First Triangle
        1, 2, 3   // Second Triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    /* Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently
    * bound vertex buffer object so afterwards we can safely unbind
    */
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs),
    * remember: do NOT unbind the EBO, keep it bound to this VAO */
    glBindVertexArray(0);

    // Uncommenting this call will result in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

WindowImpl::~WindowImpl()
{
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
    glfwMakeContextCurrent(m_wnd);
    m_mgr->SetCurrentWindow(m_id);
    auto result = glfwWindowShouldClose(m_wnd);
    return result != 0;
}

void WindowImpl::Update() const
{
    glfwMakeContextCurrent(m_wnd);
    m_mgr->SetCurrentWindow(m_id);

    // Render
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw
    testShader->Use();
    glBindVertexArray(VAO);

    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(m_wnd);  // make this loop through all current windows??
}

} }