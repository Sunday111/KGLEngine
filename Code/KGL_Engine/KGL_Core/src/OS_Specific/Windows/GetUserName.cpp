#include <KGL_Core/GetUserName.h>
#include <Windows.h>

#undef GetUserName

namespace KGL { namespace Core {

bool KGL_CORE_API GetUserName(char* buf, size_t bufsize)
{
	DWORD sz = bufsize;
	return GetUserNameA(buf, &sz) == TRUE;
}

}}