#include <algorithm>
#include <cassert>
#include <KGL_Base/UnusedVar.h>
#include <KGL_Core/Application.h>
#include <KGL_Core/SystemsManager.h>
#include <KGL_Graphics/GraphicSystem.h>
#include <KGL_Graphics/WindowManager.h>
#include <KGL_Graphics/Window.h>
#include <KGL_Graphics/Render/Shaders/ShaderProgram.h>

#include <KGL_Graphics/Render/Shaders/VertexShader.h>
#include <KGL_Graphics/Render/Shaders/FragmentShader.h>
#include <iostream>
#include <memory>
#include <string.h>
#include <vector>

using namespace KGL;
using namespace Graphics;
using namespace Core;

class TestApplication :
    public Application
{
public:
    explicit TestApplication() :
        Application()
    {
        auto gs = std::make_unique<GraphicSystem>();

        gs->GetWindowManager()->CreateWindow();
        gs->GetWindowManager()->CreateWindow();

        VertexShaderPtr vs =
            std::make_shared<VertexShader>(
                "Data\\Shaders\\Vertex\\simplest.glsl",
                nullptr, &std::cout);

        FragmentShaderPtr fs =
            std::make_shared<FragmentShader>(
                "Data\\Shaders\\Fragment\\simplest.glsl",
                nullptr, &std::cout);

        std::unique_ptr<ShaderProgram> shaderProgram =
            std::make_unique<ShaderProgram>(vs, fs, &std::cout);

        const bool useOk = shaderProgram->Use();
        assert(useOk);

        gs->AddShaderProgram(std::move(shaderProgram));

        GetSystemsManager()->RegisterSystem(std::move(gs));
    }
};

int main(int argc, const char** argv)
{
    UnusedVar(argc, argv);
    TestApplication application;
    while (application.Update());
	return 0;
}