#ifndef KGL_CORE_SYSTEM_H_INCLUDED
#define KGL_CORE_SYSTEM_H_INCLUDED

#include <KGL_Core/Common.h>
#include <KGL_Core/IObject.h>

namespace KGL { namespace Core {

class KGL_CORE_API ISystem :
    public IObject
{
public:
    virtual bool Update() = 0;
};

} }

#endif /* KGL_CORE_SYSTEM_H_INCLUDED */