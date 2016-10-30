#ifndef KGL_GRAPHICS_OBJECT_H_INCLUDED
#define KGL_GRAPHICS_OBJECT_H_INCLUDED

#include <KGL_Base/Marco.h>
#include <KGL_Core/TypeRegistry.h>
#include <KGL_Core/Object.h>
#include <KGL_Core/RTTI.h>
#include <KGL_Graphics/Common.h>

namespace KGL { namespace Graphics {

class KGL_GRAPHICS_API Object :
    public Core::Object
{
public:
	Object();
	Object(const Object&) = delete;

    DECLARE_SUPPORT_RTTI(Graphics::Object)
};

} }

#endif