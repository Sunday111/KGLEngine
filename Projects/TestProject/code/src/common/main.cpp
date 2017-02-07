#include <algorithm>
#include <cassert>
#include <KGL_Base/Marco.h>
#include <KGL_Base/UnusedVar.h>
#include <KGL_Core/ApplicationListener.h>
#include <KGL_Core/Application.h>
#include <KGL_Core/TypeRegistry.h>
#include <KGL_Core/RTTI.h>
#include <KGL_Core/SystemsManager.h>
#include <KGL_Graphics/GraphicSystem.h>
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
        auto gs = std::make_unique<Graphics::GraphicSystem>();

        for (int i = 0; i < 2; ++i)
        {
            auto widnowManager = gs->GetWindowManager();
            assert(widnowManager != nullptr);

            const int windowId = widnowManager->CreateWindow(app);
        }

        app->GetSystemsManager()->RegisterSystem(std::move(gs));
    }
};

extern "C"
{
    int __declspec(dllexport) __cdecl KGL_Run()
    {
        Core::Application app;

        auto listener = new AppListener();

        app.AddListener(listener, true);
        app.Initialize();

        while (app.Update());
        return 0;
    }
}