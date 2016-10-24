#ifndef KGL_CORE_OBJECT_H_INCLUDED
#define KGL_CORE_OBJECT_H_INCLUDED

#include <KGL_Base/Marco.h>
#include <KGL_Core/IObject.h>
#include <KGL_Core/RTTI.h>

namespace KGL { namespace Core {

class ITypeRegistry;

class Object :
    public IObject
{
public:
	Object();
    Object(const Object&) = delete;

    DECLARE_SUPPORT_RTTI(Object)
};


} }

#endif /* KGL_CORE_OBJECT_H_INCLUDED */