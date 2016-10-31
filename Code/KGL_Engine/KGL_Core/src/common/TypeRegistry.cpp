#include <algorithm>
#include <KGL_Core/TypeRegistry.h>
#include <KGL_Core/RTTI.h>
#include <unordered_map>

namespace KGL { namespace Core {

class TypeInfo::Impl
{
public:
	explicit Impl(int id, TypeInfo::CreateFromFileFn createFromFile,
		const char* tag, std::vector<int>&& parentTypes) :
		m_id(id),
		m_tag(tag == nullptr ? std::string() : tag),
		m_createResourceFn(createFromFile),
		m_parents(std::move(parentTypes))
	{

	}

	int m_id;
	std::string m_tag;
	TypeInfo::CreateFromFileFn m_createResourceFn;
	std::vector<int> m_parents;
};

TypeInfo::TypeInfo(int id, TypeInfo::CreateFromFileFn createFromFile,
	const char* tag, std::vector<int>&& parentTypes) :
	m_d(new Impl(id, createFromFile, tag, std::move(parentTypes)))
{}

TypeInfo::TypeInfo(TypeInfo&& uref) :
	m_d(uref.m_d)
{
	uref.m_d = nullptr;
}

const TypeInfo& TypeInfo::operator=(TypeInfo&& uref)
{
	m_d = uref.m_d;
	uref.m_d = nullptr;

	return *this;
}

bool TypeInfo::IsResource() const
{
	assert(m_d != nullptr);
	return !m_d->m_tag.empty();
}

int TypeInfo::TypeId() const
{
	assert(m_d != nullptr);
	return m_d->m_id;
}

ArrayView<const int> TypeInfo::ParentTypes() const
{
	return MakeArrayView(m_d->m_parents);
}
TypeInfo::operator int() const
{
	assert(m_d != nullptr);
	return m_d->m_id;
}

const char* TypeInfo::GetTypeTag() const
{
	assert(m_d != nullptr);
	return m_d->m_tag.data();
}

TypeInfo::CreateFromFileFn TypeInfo::GetCreateFromFileFn() const
{
	assert(m_d != nullptr);
	return m_d->m_createResourceFn;
}

class TypeRegistry::Impl
{
public:
	explicit Impl() :
		m_nextTypeId(0)
	{}

	std::vector<TypeInfo> types;
	int m_nextTypeId;
};


DEFINE_CLASS_RTTI(TypeRegistry, Object)

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

bool TypeRegistry::TypeRegistered(int id) const
{
	assert(m_d != nullptr);

	return std::binary_search(m_d->types.begin(), m_d->types.end(), id);
}

void TypeRegistry::RegisterType(int id, const char* typetag, TypeInfo::CreateFromFileFn createFromFile, std::vector<int>&& parents)
{
	assert(m_d != nullptr);
	m_d->types.emplace_back(id, createFromFile, typetag, std::move(parents));
	std::sort(m_d->types.begin(), m_d->types.end(),
		[](const TypeInfo& l, const TypeInfo& r)
	{
		return l.TypeId() < r.TypeId();
	});
}

bool TypeRegistry::IsTypeOf(int targetTypeId, int checkFor) const
{
	assert(m_d != nullptr);

	auto typeInfo = GetTypeById(targetTypeId);
	assert(typeInfo != nullptr);

	auto parentTypes = typeInfo->ParentTypes();
	const int parentTypesCount = parentTypes.size();

	for(int parentTypeIndex = 0; parentTypeIndex < parentTypesCount; ++parentTypeIndex)
    {
		const int parentType = parentTypes[parentTypeIndex];

        if(parentType == checkFor && IsTypeOf(parentType, checkFor))
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

ArrayView<const TypeInfo> TypeRegistry::GetTypes() const
{
	assert(m_d != nullptr);
	return MakeArrayView(m_d->types);
}

const TypeInfo* TypeRegistry::GetTypeById(int id) const
{
	assert(m_d != nullptr);

	for (auto& o : m_d->types)
	{
		if (o.TypeId() == id)
		{
			return &o;
		}
	}

	return nullptr;
}

} }