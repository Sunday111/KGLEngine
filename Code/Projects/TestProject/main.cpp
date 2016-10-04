#include <algorithm>
#include <KGL_Core/GetUserName.h>
#include <KGL_Graphics/GraphicSystem.h>
#include <KGL_Graphics/WindowManager.h>
#include <KGL_Graphics/Window.h>
#include <iostream>
#include <string.h>
#include <vector>

int main(int argc, const char** argv)
{
	using namespace KGL::Core;
	using namespace KGL::Graphics;
	using namespace std;

	const size_t size = 1024;

	char userName[size];

	if(!GetUserName(userName, size))
	{
		cout << "Error!" << endl;
		return 1;
	}

	cout << static_cast<const char*>(userName) << endl;

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