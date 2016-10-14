#ifndef KGL_CORE_IOBJECT_H_INCLUDED
#define KGL_CORE_IOBJECT_H_INCLUDED

#include <cassert>
#include "KGL_Core/Common.h"
#include "KGL_Core/FwdDecl.h"

namespace KGL { namespace Core {

// Base class for Sg objects
class KGL_CORE_API IObject
{
public:

protected:
    virtual ~IObject() = default;
};

} }

#define KGL_CORE_CREATEOBJ(T) \
    template<typename... U>\
    static T##Ptr Create(U&&... args)\
    {\
        T##Ptr::NoAddRef noAddRef;\
        return T##Ptr(new T(std::forward<U>(args)...), noAddRef);\
    }

#endif /* KGL_CORE_IOBJECT_H_INCLUDED */