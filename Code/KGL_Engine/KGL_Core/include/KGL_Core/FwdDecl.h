#ifndef KGL_CORE_FWDDECL_H_INCLUDED
#define KGL_CORE_FWDDECL_H_INCLUDED

#include <KGL_Core/References.h>
#include "KGL_Base/Reference.h"

#define KGL_CORE_FWDDECLOBJ(T) \
    class T;\
    typedef Reference<T> T##Ptr;\
    typedef Reference<const T> T##ConstPtr

namespace KGL { namespace Core {

KGL_CORE_FWDDECLOBJ(IObject);
KGL_CORE_FWDDECLOBJ(IApplication);

} }

#endif /* KGL_CORE_FWDDECL_H_INCLUDED */