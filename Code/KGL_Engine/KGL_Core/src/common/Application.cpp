#include "Application.h"
#include <KGL_Base/Marco.h>
#include <KGL_Core/SystemsManager.h>

namespace KGL { namespace Core {

Application::Application() :
    m_systemsManager(std::make_unique<SystemsManager>())
{}

Application::~Application()
{
	for (auto& l : m_listeners)
	{
		if (l.first)
		{
			SAFE_DELETE(l.second);
		}
	}
}

SystemsManager* Application::GetSystemsManager()
{
    return m_systemsManager.get();
}

bool Application::Update()
{
	assert(m_systemsManager != nullptr);
	return m_systemsManager->Update();
}

bool Application::AddListener(IApplicationListener* listener, bool destroy)
{
	for (auto& l : m_listeners)
	{
		if (l.second == listener)
		{
			return false;
		}
	}

	m_listeners.push_back(std::make_pair(destroy, listener));

	return true;
}

void Application::Initialize()
{
	for (auto k : m_listeners)
	{
		k.second->OnInitialize(this);
	}
}

} }