#ifndef KGL_CORE_CREATE_INSTANCE_H_INCLUDED
#define KGL_CORE_CREATE_INSTANCE_H_INCLUDED

#include <KGL_Core/Common.h>
#include <KGL_Core/FwdDecl.h>
#include <KGL_Core/IApplication.h>

namespace KGL { namespace Core {

enum class KGL_CORE_API PointerType
{
	Shared,
	Unique
};

template<class T, PointerType pt>
class PointerTypeHelper;

template<class T>
class PointerTypeHelper<T, PointerType::Shared>
{
public:
	using Pointer = std::shared_ptr<T>;
};

template<class T>
class PointerTypeHelper<T, PointerType::Unique>
{
public:
	using Pointer = std::unique_ptr<T>;
};

template<class T, PointerType pt>
class KGL_CORE_API InstanceCreator
{
public:
	using Pointer = typename PointerTypeHelper<T, pt>::Pointer;

	static Pointer CreateInstance();
};

} }

#endif /* KGL_CORE_CREATE_INSTANCE_H_INCLUDED */