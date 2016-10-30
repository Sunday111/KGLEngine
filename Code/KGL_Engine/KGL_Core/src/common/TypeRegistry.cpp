#include <KGL_Core/TypeRegistry.h>
#include <KGL_Core/RTTI.h>
#include <unordered_map>

namespace KGL { namespace Core {

class TypeRegistry::Impl
{
public:
	explicit Impl() :
		m_nextTypeId(0)
	{}

	std::unordered_map<int, std::vector<int>> typeMap;
	int m_nextTypeId;
};


DEFINE_SUPPORT_RTTI(TypeRegistry, Object)

TypeRegistry* TypeRegistry::GetInstance()
{
    static TypeRegistry instance;
    return &instance;
}

TypeRegistry::TypeRegistry() :
	m_d(new Impl)
{}

TypeRegistry::~TypeRegistry()
{
	assert(m_d != nullptr);
	delete m_d;
}

bool TypeRegistry::TypeRegistered(int typeId) const
{
	assert(m_d != nullptr);
    return m_d->typeMap.find(typeId) != m_d->typeMap.end();
}

void TypeRegistry::RegisterType(int typeId, std::vector<int>&& parents)
{
	m_d->typeMap[typeId] = std::move(parents);
}

bool TypeRegistry::IsTypeOf(int targetTypeId, int checkFor) const
{
    auto iTypeToParents = m_d->typeMap.find(targetTypeId);

    assert(iTypeToParents != m_d->typeMap.end());

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
    return m_d->m_nextTypeId++;
}

} }