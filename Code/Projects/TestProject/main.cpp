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

using namespace KGL;
using namespace Core;
using namespace Graphics;

class AppListener :
    public IApplicationListener
{
public:
	void OnInitialize(IApplication* app) override
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

    DECLARE_SUPPORT_RTTI(AppListener)
};

DEFINE_SUPPORT_RTTI(AppListener)

int main(int argc, const char** argv)
{
	UnusedVar(argc, argv);
	auto app = Core::InstanceCreator<IApplication,PointerType::Unique>::CreateInstance();

    auto listener = new AppListener();

	app->AddListener(listener, true);
	app->Initialize();

	while (app->Update());
	return 0;
}