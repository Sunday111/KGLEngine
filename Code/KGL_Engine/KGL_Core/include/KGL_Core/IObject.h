#ifndef KGL_CORE_IOBJECT_H_INCLUDED
#define KGL_CORE_IOBJECT_H_INCLUDED

#include <cassert>
#include "KGL_Core/Common.h"

namespace KGL { namespace Core {

class KGL_CORE_API IObject
{
public:
    virtual ~IObject() {};
};

} }

#endif /* KGL_CORE_IOBJECT_H_INCLUDED */