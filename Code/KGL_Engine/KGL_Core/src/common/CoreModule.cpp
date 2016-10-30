#include <KGL_Core/CoreModule.h>
#include <KGL_Core/RTTI.h>

namespace KGL { namespace Core {

DEFINE_SUPPORT_RTTI(CoreModule, Module)

class CoreModule::Impl
{
public:
	explicit Impl() :
		m_nextModuleId(1),
		m_id(0)
	{}

	int m_nextModuleId;
	int m_id;
};

int CoreModule::GetModuleId()
{
	assert(m_d != nullptr);
	return m_d->m_id;
}

int CoreModule::GetNextModuleId()
{
	assert(m_d != nullptr);
	return m_d->m_nextModuleId++;
}

CoreModule* CoreModule::GetInstance()
{
	static CoreModule instance;
	return &instance;
}

CoreModule::CoreModule() :
	m_d(new Impl)
{}

CoreModule::~CoreModule()
{
	assert(m_d != nullptr);
	delete m_d;
}

Module* GetModule()
{
	return CoreModule::GetInstance();
}

} }