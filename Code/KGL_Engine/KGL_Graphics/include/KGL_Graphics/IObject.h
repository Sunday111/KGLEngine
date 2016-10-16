#ifndef KGL_GRAPHICS_IOBJECT_H_INCLUDED
#define KGL_GRAPHICS_IOBJECT_H_INCLUDED

#include <KGL_Graphics/Common.h>

namespace KGL { namespace Graphics {

class KGL_GRAPHICS_API IObject
{
public:
	virtual ~IObject() = 0;
};

} }

#endif /* KGL_GRAPHICS_IOBJECT_H_INCLUDED */