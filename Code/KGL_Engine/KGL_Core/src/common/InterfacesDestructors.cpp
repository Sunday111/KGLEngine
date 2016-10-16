#include <KGL_Core/IObject.h>
#include <KGL_Core/ISystem.h>
#include <KGL_Core/ISystemsManager.h>

namespace KGL { namespace Core {

#define IMPLEMENT_INTERFACE_DTOR(type)\
	type::~type() = default;

IMPLEMENT_INTERFACE_DTOR(IObject)
IMPLEMENT_INTERFACE_DTOR(ISystem)

} }