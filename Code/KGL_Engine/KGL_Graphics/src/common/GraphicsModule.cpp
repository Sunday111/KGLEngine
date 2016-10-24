#include "GraphicsModule.h"
#include <KGL_Graphics/IModule.h>

namespace KGL { namespace Graphics {

DEFINE_SUPPORT_RTTI(GraphicsModule, Graphics::Object)

int GraphicsModule::GetModuleId()
{
	return m_id;
}

GraphicsModule* GraphicsModule::Instance()
{
	static GraphicsModule instance;
	return &instance;
}

GraphicsModule::GraphicsModule() :
	m_id(Core::GetCoreModule()->GetNextModuleId())
{}

Core::IModule* GetModule()
{
	return GraphicsModule::Instance();
}

} }