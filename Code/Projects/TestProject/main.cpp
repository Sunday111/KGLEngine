#include <algorithm>
#include <cassert>
#include <KGL_Base/UnusedVar.h>
#include <KGL_Core/CreateInstance.h>
#include <KGL_Core/IApplication.h>
#include <KGL_Core/ISystemsManager.h>
#include <KGL_Graphics/GraphicSystem.h>
#include <KGL_Graphics/WindowManager.h>
#include <KGL_Graphics/Window.h>
#include <iostream>
#include <memory>
#include <string.h>
#include <vector>

using namespace KGL;
using namespace Graphics;
using namespace Core;

class AppListener : public IApplicationListener
{
public:
	void OnInitialize(IApplication* app) override
	{
		auto gs = std::make_unique<GraphicSystem>();
		
		gs->GetWindowManager()->CreateWindow();
		gs->GetWindowManager()->CreateWindow();

		for (int i = 0; i < 10; ++i)
		{
			gs->GetWindowManager()->CreateWindow();
		}

		app->GetSystemsManager()->RegisterSystem(std::move(gs));
	}
};

int main(int argc, const char** argv)
{
	UnusedVar(argc, argv);
	auto app = InstanceCreator<IApplication, PointerType::Unique>::CreateInstance();

	app->AddListener(new AppListener(), true);
	app->Initialize();

	while (app->Update());
	return 0;
}