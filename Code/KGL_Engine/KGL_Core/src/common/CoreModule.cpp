#include "CoreModule.h"

namespace KGL { namespace Core { namespace {

}

int CoreModule::GetModuleId()
{
	return m_id;
}

int CoreModule::GetNextModuleId()
{
	return m_nextModuleId++;
}

CoreModule* CoreModule::Instance()
{
	static CoreModule instance;
	return &instance;
}

CoreModule::CoreModule() :
	m_nextModuleId(1),
	m_id(0)
{}

IModule* GetModule()
{
	return CoreModule::Instance();
}

ICoreModule* GetCoreModule()
{
	return CoreModule::Instance();
}

} }