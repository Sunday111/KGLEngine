#include <KGL_Core/GetUserName.h>
#include <KGL_Graphics/GraphicsTestFunction.h>
#include <iostream>
#include <string.h>

// GLFW
#include <GLFW/glfw3.h>

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

	GraphicsTestFunction();

	return 0;
}