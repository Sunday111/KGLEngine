#ifndef KGL_CORE_TYPE_REGISTRY_H_INCLUDED
#define KGL_CORE_TYPE_REGISTRY_H_INCLUDED

#include <KGL_Core/ITypeRegistry.h>
#include <KGL_Core/RTTI.h>
#include "Object.h"
#include <vector>
#include <unordered_map>

namespace KGL { namespace Core {

class TypeRegistry :
    public virtual ITypeRegistry,
    public virtual Object
{
public:

    bool TypeRegistered(int typeId) const override;
    void RegisterType(int typeId, std::vector<int>&& parents) override;
    bool IsTypeOf(int targetTypeId, int checkFor) const override;
    int GetNextTypeId();

    static TypeRegistry* GetInstance();

    DECLARE_SUPPORT_RTTI(TypeRegistry, Object)

private:
    explicit TypeRegistry() :
        m_nextTypeId(0)
    {}

    std::unordered_map<int, std::vector<int>> typeMap;
    int m_nextTypeId;
};

} }

#endif /* KGL_CORE_TYPE_REGISTRY_H_INCLUDED */