#ifndef KGL_CORE_REFERENCES_H_INCLUDED
#define KGL_CORE_REFERENCES_H_INCLUDED

#include <KGL_Core/Common.h>

namespace KGL { namespace Core {

class IObject;

} }

namespace KGL
{

void KGL_CORE_API ReferenceAddRef(const Core::IObject* p);
void KGL_CORE_API ReferenceReleaseRef(const Core::IObject* p);
int KGL_CORE_API ReferenceCountRef(const Core::IObject* p);

}

#endif /* KGL_CORE_REFERENCES_H_INCLUDED */