#ifndef KGL_GRAPHICS_OBJECT_H_INCLUDED
#define KGL_GRAPHICS_OBJECT_H_INCLUDED

#include <KGL_Core/IObject.h>

namespace KGL { namespace Graphics {

class Object : public Core::IObject
{
public:
	Object() = default;
	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;
};

} }

#endif /* KGL_GRAPHICS_OBJECT_H_INCLUDED */