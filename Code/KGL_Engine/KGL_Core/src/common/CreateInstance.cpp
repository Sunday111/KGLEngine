#include "KGL_Core/CreateInstance.h"
#include "Application.h"

namespace KGL { namespace Core {


template<class T, PointerType pt>
class CreateHelper;

template<class T>
class CreateHelper<T, PointerType::Shared>
{
public:
	using Pointer = typename PointerTypeHelper<T, PointerType::Shared>::Pointer;

	template<typename... U>
	static Pointer Create(U&&... args)
	{
		return std::make_shared<T>(std::forward<U>(args)...);
	}
};

template<class T>
class CreateHelper<T, PointerType::Unique>
{
public:
	using Pointer = typename PointerTypeHelper<T, PointerType::Unique>::Pointer;

	template<typename... U>
	static Pointer Create(U&&... args)
	{
		return std::make_unique<T>(std::forward<U>(args)...);
	}
};

#define InstanceCreatorInstantiation(Interface, Implementation, pointerType)\
template<>\
typename InstanceCreator<Interface, pointerType>::Pointer \
InstanceCreator<Interface, pointerType>::CreateInstance() \
{ \
	using Pointer = typename InstanceCreator<Interface, pointerType>::Pointer; \
 \
	return static_cast<Pointer>(CreateHelper<Implementation, pointerType>::Create()); \
} \
template class InstanceCreator<Interface, pointerType>

InstanceCreatorInstantiation(IApplication, Application, PointerType::Unique);
InstanceCreatorInstantiation(IApplication, Application, PointerType::Shared);

} }