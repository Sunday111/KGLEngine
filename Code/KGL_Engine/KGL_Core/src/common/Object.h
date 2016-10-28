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
	DECLARE_SUPPORT_RTTI(Object)

public:
	Object();
    Object(const Object&) = delete;

private:
	friend void AddReference(const IObject* p);
	friend void RemoveReference(const IObject* p);
	friend int GetReferencesCount(const IObject* p);

	mutable int m_referencesCount;
};


} }

#endif /* KGL_CORE_OBJECT_H_INCLUDED */