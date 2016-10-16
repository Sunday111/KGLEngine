#include <iostream>
#include <KGL_Graphics/CreateInstance.h>
#include <KGL_Graphics/Render/Shaders/ShaderType.h>
#include <KGL_Graphics/Render/Shaders/IShader.h>
#include <KGL_Graphics/Render/Shaders/IShaderProgram.h>
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

	auto vs = InstanceCreator<IShader, PointerType::Unique, ShaderType>::CreateInstance(ShaderType::Vertex);
	const bool vsCompileOk = vs->Compile("Data\\Shaders\\Vertex\\simplest.glsl", nullptr, &std::cout);
	assert(vsCompileOk);

	auto fs = InstanceCreator<IShader, PointerType::Unique, ShaderType>::CreateInstance(ShaderType::Fragment);
	const bool fsCompileOk = fs->Compile("Data\\Shaders\\Fragment\\simplest.glsl", nullptr, &std::cout);
	assert(fsCompileOk);

	/* Create shader program instance */
	testShader = InstanceCreator<IShaderProgram, PointerType::Unique>::CreateInstance();

	/* Add vertex shader to shader program */
	const bool addVsOk = testShader->AddShader(std::move(vs), false);
	assert(addVsOk);

	/* Add fragment shader to shader program */
	const bool addFsOk = testShader->AddShader(std::move(fs), false);
	assert(addVsOk);

	/* Link shaders into shader prgram */
	testShader->Link(&std::cout);

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