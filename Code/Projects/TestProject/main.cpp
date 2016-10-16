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

class AppListener : public KGL::Core::IApplicationListener
{
public:
	void OnInitialize(KGL::Core::IApplication* app) override
	{
		auto gs = std::make_unique<KGL::Graphics::GraphicSystem>();
		
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
	using namespace KGL;
	using namespace KGL::Core;

	UnusedVar(argc, argv);
	auto app = InstanceCreator<IApplication,PointerType::Unique>::CreateInstance();

	app->AddListener(new AppListener(), true);
	app->Initialize();

	while (app->Update());
	return 0;
}