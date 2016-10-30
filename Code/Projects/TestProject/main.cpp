#include <algorithm>
#include <cassert>
#include <KGL_Base/Marco.h>
#include <KGL_Base/UnusedVar.h>
#include <KGL_Core/ApplicationListener.h>
#include <KGL_Core/Application.h>
#include <KGL_Core/CreateInstance.h>
#include <KGL_Core/ITypeRegistry.h>
#include <KGL_Core/RTTI.h>
#include <KGL_Core/SystemsManager.h>
#include <KGL_Graphics/CreateInstance.h>
#include <KGL_Graphics/IGraphicSystem.h>
#include <KGL_Graphics/WindowManager.h>
#include <iostream>
#include <memory>
#include <string.h>
#include <vector>
#include <typeinfo>

using namespace KGL;
using namespace Core;
using namespace Graphics;

class AppListener :
    public ApplicationListener
{
public:
	void OnInitialize(Core::Application* app) override
	{
        auto gs = Graphics::InstanceCreator<
            Graphics::IGraphicSystem,
            PointerType::Unique>::CreateInstance();

		for (int i = 0; i < 2; ++i)
		{
			gs->GetWindowManager()->CreateWindow();
		}

		app->GetSystemsManager()->RegisterSystem(std::move(gs));
	}
};

int main(int argc, const char** argv)
{
	UnusedVar(argc, argv);
	Core::Application app;

    auto listener = new AppListener();

	app.AddListener(listener, true);
	app.Initialize();

	while (app.Update());
	return 0;
}