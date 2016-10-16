#ifndef KGL_CORE_CREATE_INSTANCE_H_INCLUDED
#define KGL_CORE_CREATE_INSTANCE_H_INCLUDED

#include <KGL_Base/SmartPointers.h>
#include <KGL_Core/Common.h>

namespace KGL { namespace Core {

template<class T, PointerType pt, typename... U>
class KGL_CORE_API InstanceCreator
{
public:
	using Pointer = typename PointerTypeHelper<T, pt>::Pointer;

	static Pointer CreateInstance(U&&...);
};

} }

#endif /* KGL_CORE_CREATE_INSTANCE_H_INCLUDED */