#include "Object.h"

namespace KGL { namespace Core {

void AddReference(const IObject* p)
{
	++static_cast<const Object*>(p)->m_referencesCount;
}

void RemoveReference(const IObject* p)
{
	--static_cast<const Object*>(p)->m_referencesCount;
}

int GetReferencesCount(const IObject* p)
{
	return static_cast<const Object*>(p)->m_referencesCount;
}

} }