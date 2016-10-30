#include <cassert>
#include <KGL_Base/Marco.h>
#include <KGL_Core/System.h>
#include <KGL_Core/SystemsManager.h>
#include <KGL_Core/TypeRegistry.h>
#include <KGL_Core/RTTI.h>

namespace KGL { namespace Core {

class SystemsManager::Impl
{
public:
	std::vector<std::unique_ptr<System>> m_systems;
};

SystemsManager::SystemsManager() :
	m_d(new Impl)
{}

SystemsManager::~SystemsManager()
{
	assert(m_d != nullptr);
	delete m_d;
}

DEFINE_SUPPORT_RTTI(SystemsManager, Object)

bool SystemsManager::RegisterSystem(std::unique_ptr<System> system)
{
	assert(m_d != nullptr);

	for (auto& s : m_d->m_systems)
	{
		if (s == system)
		{
			return false;
		}
	}

	m_d->m_systems.push_back(std::move(system));
	return true;
}

bool SystemsManager::Update()
{
	assert(m_d != nullptr);

	for (auto& s : m_d->m_systems)
	{
		if (!s->Update())
		{
			return false;
		}
	}

	return true;
}

} }