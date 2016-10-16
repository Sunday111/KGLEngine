#include <cassert>
#include <KGL_Base/Marco.h>
#include <KGL_Core/ISystem.h>
#include "SystemsManager.h"

namespace KGL { namespace Core {

bool SystemsManager::RegisterSystem(std::unique_ptr<ISystem> system)
{
	for (auto& s : m_systems)
	{
		if (s == system)
		{
			return false;
		}
	}

	m_systems.push_back(std::move(system));
	return true;
}

bool SystemsManager::Update()
{
	for (auto& s : m_systems)
	{
		if (!s->Update())
		{
			return false;
		}
	}

	return true;
}

} }