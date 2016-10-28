#include "Object.h"
#include <KGL_Core/ITypeRegistry.h>

namespace KGL { namespace Core {

Object::Object() :
	m_referencesCount(0)
{}

DEFINE_SUPPORT_RTTI(Object)

} }