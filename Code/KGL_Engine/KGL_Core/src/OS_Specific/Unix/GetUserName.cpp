#include <KGL_Core/GetUserName.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>

namespace KGL { namespace Core {

bool KGL_CORE_API GetUserName(char* buf, std::size_t bufsize)
{
    const char* login = getpwuid(getuid())->pw_name;

    if(login == nullptr)
    {
        return false;
    }

    const std::size_t len = strlen(login);

    if(len >= bufsize)
    {
        return false;
    }

    memcpy(buf, login, len);
    buf[len] = '\0';

    return true;
}

}}