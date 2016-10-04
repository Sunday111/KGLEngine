#include <algorithm>
#include <KGL_Graphics/GraphicSystem.h>
#include <KGL_Graphics/WindowManager.h>
#include <KGL_Graphics/Window.h>
#include <iostream>
#include <string.h>
#include <vector>

int main(int argc, const char** argv)
{
    using namespace KGL::Graphics;
    using namespace std;

    GraphicSystem system;

    WindowManager* wndMgr = system.GetWindowManager();

    std::vector<Window> windows;
    windows.emplace_back(wndMgr);
    windows.emplace_back(wndMgr);

    while (!windows.empty())
    {
        windows.erase(std::remove_if(windows.begin(), windows.end(),
            [](const Window& wnd)
        {
            return wnd.ShouldClose();
        }), windows.end());

        system.Update();
    }

	return 0;
}