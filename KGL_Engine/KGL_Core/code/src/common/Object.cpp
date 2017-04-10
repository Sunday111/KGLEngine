#include <KGL_Core/Object.h>
#include <KGL_Core/TypeRegistry.h>

namespace KGL { namespace Core {

class Object::Impl
{
public:
    Impl() :
        m_referencesCount(0)
    {}

    int m_referencesCount;
};

Object::~Object()
{
    SafeDelete(m_d);
}

int Object::TypeId()
{
    static const int typeId = TypeRegistry::GetInstance()->GetNextTypeId();
    return typeId;
}

Object::Object() :
    m_d(new Impl)
{}

void AddReference(const Object* p)
{
    ++p->m_d->m_referencesCount;
}

int RemoveReference(const Object* p)
{
    int result = --p->m_d->m_referencesCount;

    if (result == 0)
    {
        delete p;
    }

    return result;
}

int GetReferencesCount(const Object* p)
{
    return p->m_d->m_referencesCount;
}


} }