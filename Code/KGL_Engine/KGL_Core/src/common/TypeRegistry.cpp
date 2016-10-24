#include "TypeRegistry.h"

namespace KGL { namespace Core {

DEFINE_SUPPORT_RTTI(TypeRegistry, Object)

TypeRegistry* TypeRegistry::GetInstance()
{
    static TypeRegistry instance;
    return &instance;
}

bool TypeRegistry::TypeRegistered(int typeId) const
{
    return typeMap.find(typeId) != typeMap.end();
}

void TypeRegistry::RegisterType(int typeId, std::vector<int>&& parents)
{
    typeMap[typeId] = std::move(parents);
}

bool TypeRegistry::IsTypeOf(int targetTypeId, int checkFor) const
{
    auto iTypeToParents = typeMap.find(targetTypeId);

    assert(iTypeToParents != typeMap.end());

    for(int parent : iTypeToParents->second)
    {
        if(parent == checkFor && IsTypeOf(parent, checkFor))
        {
            return true;
        }
    }

    return false;
}

int TypeRegistry::GetNextTypeId()
{
    return m_nextTypeId++;
}

ITypeRegistry* GetTypeRegistry()
{
    return TypeRegistry::GetInstance();
}

} }