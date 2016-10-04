#include <KGL_Core/GetUserName.h>
#include <KGL_Graphics/GraphicSystem.h>
#include <iostream>
#include <string.h>

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

	return 0;
}