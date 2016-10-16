#ifndef KGL_CORE_IOBJECT_H_INCLUDED
#define KGL_CORE_IOBJECT_H_INCLUDED

#include <cassert>
#include "KGL_Core/Common.h"

namespace KGL { namespace Core {

class KGL_CORE_API IObject
{
public:

protected:
    virtual ~IObject() = 0;
};

} }

#endif /* KGL_CORE_IOBJECT_H_INCLUDED */