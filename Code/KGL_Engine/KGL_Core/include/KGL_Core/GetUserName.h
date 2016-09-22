#ifndef KGL_CORE_GET_USER_NAME_H_INCLUDED
#define KGL_CORE_GET_USER_NAME_H_INCLUDED

#include <cstddef>
#include <KGL_Core/Common.h>

namespace KGL { namespace Core {

bool KGL_CORE_API GetUserName(char* buf, std::size_t bufsize);

}}

#endif /*KGL_CORE_GET_USER_NAME_H_INCLUDED*/