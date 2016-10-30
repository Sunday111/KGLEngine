#ifndef KGL_OBJECT_H_INCLUDED
#define KGL_OBJECT_H_INCLUDED

#include <KGL_Base/Marco.h>
#include <KGL_Core/Common.h>

namespace KGL { namespace Core {

class Object;

KGL_CORE_API void AddReference(const Object* p);
KGL_CORE_API void RemoveReference(const Object* p);
KGL_CORE_API int GetReferencesCount(const Object* p);

class KGL_CORE_API Object
{
public:
	virtual int GetTypeId() const = 0;
	virtual bool IsTypeOf(int typeId) const = 0;
	virtual ~Object();

	static int TypeId();

protected:
	explicit Object();

private:
	friend void KGL_CORE_API AddReference(const Object* p);
	friend void KGL_CORE_API RemoveReference(const Object* p);
	friend int KGL_CORE_API GetReferencesCount(const Object* p);

	class Impl;
	Impl* m_d;
};

} }

#endif