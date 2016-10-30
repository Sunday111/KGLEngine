#include <KGL_Core/Application.h>
#include <KGL_Core/ApplicationListener.h>
#include <KGL_Core/System.h>
#include <KGL_Core/TypeRegistry.h>
#include <KGL_Core/RTTI.h>
#include <KGL_Core/SystemsManager.h>

namespace KGL { namespace Core {

class Application::Impl
{
public:
	Impl() :
		m_systemsManager(std::make_unique<SystemsManager>())
	{}

	std::unique_ptr<SystemsManager> m_systemsManager;
	std::vector<std::pair<bool, ApplicationListener*>> m_listeners;
};

DEFINE_SUPPORT_RTTI(Application, Object)

Application::Application() :
    m_d(new Impl)
{}

Application::~Application()
{
	assert(m_d != nullptr);

	for (auto& l : m_d->m_listeners)
	{
		if (l.first)
		{
			SAFE_DELETE(l.second);
		}
	}

	delete m_d;
}

SystemsManager* Application::GetSystemsManager()
{
	assert(m_d != nullptr);
	return m_d->m_systemsManager.get();
}

bool Application::Update()
{
	assert(m_d != nullptr && m_d->m_systemsManager != nullptr);
	return m_d->m_systemsManager->Update();
}

bool Application::AddListener(ApplicationListener* listener, bool destroy)
{
	assert(m_d != nullptr);

	for (auto& l : m_d->m_listeners)
	{
		if (l.second == listener)
		{
			return false;
		}
	}

	m_d->m_listeners.push_back(std::make_pair(destroy, listener));

	return true;
}

void Application::Initialize()
{
	assert(m_d != nullptr);

	for (auto k : m_d->m_listeners)
	{
		assert(k.second != nullptr);
		k.second->OnInitialize(this);
	}
}

} }