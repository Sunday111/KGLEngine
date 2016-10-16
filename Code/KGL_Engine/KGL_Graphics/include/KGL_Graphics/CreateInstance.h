#ifndef KGL_GRAPHICS_CREATE_INSTANCE_H_INCLUDED
#define KGL_GRAPHICS_CREATE_INSTANCE_H_INCLUDED

#include <KGL_Base/SmartPointers.h>
#include <KGL_Graphics/Common.h>

namespace KGL { namespace Graphics {

template<class T, PointerType pt, typename... U>
class KGL_GRAPHICS_API InstanceCreator
{
public:
	using Pointer = typename PointerTypeHelper<T, pt>::Pointer;

	static Pointer CreateInstance(U&&...);
};

} }

#endif /* KGL_GRAPHICS_CREATE_INSTANCE_H_INCLUDED */