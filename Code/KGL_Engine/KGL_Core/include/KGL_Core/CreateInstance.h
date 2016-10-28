#ifndef KGL_CORE_CREATE_INSTANCE_H_INCLUDED
#define KGL_CORE_CREATE_INSTANCE_H_INCLUDED

#include <KGL_Base/SmartPointers.h>
#include <KGL_Core/Common.h>
#include <KGL_Core/Ptr.h>

namespace KGL { namespace Core {

template<class T, typename... U>
class KGL_CORE_API InstanceCreator
{
public:
	using Pointer = Ptr<T>;

	static Pointer CreateInstance(U...);
};

} }

#endif /* KGL_CORE_CREATE_INSTANCE_H_INCLUDED */