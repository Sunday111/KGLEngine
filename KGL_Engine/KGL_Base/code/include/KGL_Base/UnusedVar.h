#ifndef KGL_BASE_UNUSED_VAR_H_INCLUDED
#define KGL_BASE_UNUSED_VAR_H_INCLUDED

namespace KGL {

template<typename T, typename... U>
void UnusedVar(T&&, U&&...) {}

}

#endif /*KGL_BASE_UNUSED_VAR_H_INCLUDED*/