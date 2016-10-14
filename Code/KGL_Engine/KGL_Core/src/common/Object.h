#ifndef KGL_CORE_OBJECT_H_INCLUDED
#define KGL_CORE_OBJECT_H_INCLUDED

#include <KGL_Core/IObject.h>
#include <KGL_Core/References.h>

namespace KGL { namespace Core {

class Object : public IObject
{
public:
    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;

protected:
    Object() : m_ref(1) {}
    ~Object() override { assert(m_ref == 0); }

private:

    friend void KGL::ReferenceAddRef(const KGL::Core::IObject* p);
    friend void KGL::ReferenceReleaseRef(const KGL::Core::IObject* p);
    friend int KGL::ReferenceCountRef(const KGL::Core::IObject* p);

    mutable int m_ref;
};

} }

#endif /* KGL_CORE_OBJECT_H_INCLUDED */