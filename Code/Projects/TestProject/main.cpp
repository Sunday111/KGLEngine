#include <algorithm>
#include <KGL_Core/Application.h>
#include <KGL_Core/SystemsManager.h>
#include <KGL_Graphics/GraphicSystem.h>
#include <KGL_Graphics/WindowManager.h>
#include <KGL_Graphics/Window.h>
#include <iostream>
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

        GetSystemsManager()->RegisterSystem(std::move(gs));
    }
};

int main(int argc, const char** argv)
{
    TestApplication application;
    while (application.Update());
	return 0;
}