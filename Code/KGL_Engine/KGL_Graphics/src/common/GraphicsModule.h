#ifndef KGL_GRAPHICS_GRAPHICS_MODULE_H_INCLUDED
#define KGL_GRAPHICS_GRAPHICS_MODULE_H_INCLUDED

#include <KGL_Core/ICoreModule.h>

namespace KGL { namespace Graphics {

class GraphicsModule : public Core::IModule
{
public:
	int GetModuleId() override;

	static GraphicsModule* Instance();

private:
	GraphicsModule();

	const int m_id;
};

} }

#endif /* KGL_GRAPHICS_GRAPHICS_MODULE_H_INCLUDED */