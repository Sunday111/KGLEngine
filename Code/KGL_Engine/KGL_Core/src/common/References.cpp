#include <KGL_Core/References.h>
#include "Object.h"

namespace KGL
{

void KGL_CORE_API ReferenceAddRef(const Core::IObject* p)
{
	auto po = static_cast<const Core::Object*>(p);

	assert(po->m_ref > 0);

	++po->m_ref;
}

void KGL_CORE_API ReferenceReleaseRef(const Core::IObject* p)
{
	auto po = static_cast<const Core::Object*>(p);

	assert(po->m_ref > 0);

	if (--po->m_ref == 0)
	{
		delete po;
	}
}

int KGL_CORE_API ReferenceCountRef(const Core::IObject* p)
{
	auto po = static_cast<const Core::Object*>(p);

	assert(po->m_ref > 0);

	return po->m_ref;
}

}