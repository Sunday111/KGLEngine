#include <algorithm>
#include <cassert>
#include <KGL_Base/Marco.h>
#include <KGL_Base/UnusedVar.h>
#include <KGL_Core/CreateInstance.h>
#include <KGL_Core/IApplication.h>
#include <KGL_Core/ISystemsManager.h>
#include <KGL_Core/RTTI.h>
#include <KGL_Core/ITypeRegistry.h>
#include <KGL_Graphics/CreateInstance.h>
#include <KGL_Graphics/IGraphicSystem.h>
#include <KGL_Graphics/WindowManager.h>
#include <iostream>
#include <memory>
#include <string.h>
#include <vector>
#include <typeinfo>

class AppListener :
    public KGL::Core::IApplicationListener
{
public:
	void OnInitialize(KGL::Core::IApplication* app) override
	{
        auto gs = KGL::Graphics::InstanceCreator<
            KGL::Graphics::IGraphicSystem,
            KGL::PointerType::Unique>::CreateInstance();
		
		gs->GetWindowManager()->CreateWindow();
		gs->GetWindowManager()->CreateWindow();

		for (int i = 0; i < 10; ++i)
		{
			gs->GetWindowManager()->CreateWindow();
		}

		app->GetSystemsManager()->RegisterSystem(std::move(gs));
	}

    DECLARE_SUPPORT_RTTI(AppListener)
};

DEFINE_SUPPORT_RTTI(AppListener)

int main(int argc, const char** argv)
{
	using namespace KGL;
	using namespace KGL::Core;

	UnusedVar(argc, argv);
	auto app = InstanceCreator<IApplication,PointerType::Unique>::CreateInstance();

    auto listener = new AppListener();

	app->AddListener(listener, true);
	app->Initialize();

	while (app->Update());
	return 0;
}