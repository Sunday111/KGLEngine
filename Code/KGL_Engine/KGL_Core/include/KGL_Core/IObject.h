#ifndef KGL_CORE_IOBJECT_H_INCLUDED
#define KGL_CORE_IOBJECT_H_INCLUDED

#include <cassert>
#include "KGL_Core/Common.h"

namespace KGL { namespace Core {

class KGL_CORE_API IObject
{
public:
    virtual int GetTypeId() const = 0;
    virtual bool IsTypeOf(int typeId) const = 0;
    virtual ~IObject() {};
};

KGL_CORE_API void AddReference(const IObject* p);
KGL_CORE_API void RemoveReference(const IObject* p);
KGL_CORE_API int GetReferencesCount(const IObject* p);

} }

#endif /* KGL_CORE_IOBJECT_H_INCLUDED */