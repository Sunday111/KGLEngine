#ifndef KGL_CORE_ITYPE_REGISTRY_H_INCLUDED
#define KGL_CORE_ITYPE_REGISTRY_H_INCLUDED

#include <KGL_Core/Object.h>
#include <vector>

namespace KGL { namespace Core {

class KGL_CORE_API ITypeRegistry : public Object
{
public:
    virtual bool TypeRegistered(int typeId) const = 0;
    virtual void RegisterType(int typeId, std::vector<int>&& parents) = 0;
    virtual bool IsTypeOf(int targetTypeId, int checkFor) const = 0;
    virtual int GetNextTypeId() = 0;
};

KGL_CORE_API ITypeRegistry* GetTypeRegistry();

} }


#endif /*KGL_CORE_ITYPE_REGISTRY__H_INCLUDED*/