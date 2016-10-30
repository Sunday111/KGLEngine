#ifndef KGL_GRAPHICS_OBJECT_H_INCLUDED
#define KGL_GRAPHICS_OBJECT_H_INCLUDED

#include <KGL_Base/Marco.h>
#include <KGL_Core/ITypeRegistry.h>
#include <KGL_Core/Object.h>
#include <KGL_Core/RTTI.h>

namespace KGL { namespace Graphics {

class Object :
    public Core::Object
{
public:
	Object();
	Object(const Object&) = delete;

    DECLARE_SUPPORT_RTTI(Graphics::Object)
};

} }

#endif /* KGL_GRAPHICS_OBJECT_H_INCLUDED */