#ifndef KGL_GRAPHICS_GRAPHICS_MODULE_H_INCLUDED
#define KGL_GRAPHICS_GRAPHICS_MODULE_H_INCLUDED

#include "Object.h"
#include <KGL_Core/CoreModule.h>
#include <KGL_Core/RTTI.h>

namespace KGL { namespace Graphics {

class GraphicsModule :
    public virtual Core::Module,
    public virtual Graphics::Object
{
public:
	int GetModuleId() override;
	static GraphicsModule* Instance();

    DECLARE_SUPPORT_RTTI(GraphicsModule, Graphics::Object)
private:
	GraphicsModule();

	const int m_id;
};

} }

#endif /* KGL_GRAPHICS_GRAPHICS_MODULE_H_INCLUDED */