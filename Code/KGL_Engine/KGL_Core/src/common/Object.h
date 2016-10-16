#ifndef KGL_CORE_OBJECT_H_INCLUDED
#define KGL_CORE_OBJECT_H_INCLUDED

#include <KGL_Core/IObject.h>

namespace KGL { namespace Core {

class Object : public IObject
{
public:
	Object() = default;
    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;
};

} }

#endif /* KGL_CORE_OBJECT_H_INCLUDED */