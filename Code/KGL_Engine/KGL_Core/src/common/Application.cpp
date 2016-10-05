#include "ApplicationImpl.h"
#include <cassert>
#include <KGL_Core/SystemsManager.h>

#include <KGL_Core/Application.h>

namespace KGL { namespace Core {

Application::Application() :
    m_d(new ApplicationImpl())
{}

Application::Application(Application&& uref) :
    m_d(uref.m_d)
{
    uref.m_d = nullptr;
}

Application::~Application()
{
    if (m_d != nullptr)
    {
        delete m_d;
    }
}

bool Application::Update()
{
    assert(m_d != nullptr);

    return m_d->GetSystemsManager()->Update();
}

Application& Application::operator=(Application&& uref)
{
    if (m_d != nullptr)
    {
        delete m_d;
    }

    m_d = uref.m_d;
    uref.m_d = nullptr;

    return *this;
}

SystemsManager* Application::GetSystemsManager()
{
    if (m_d == nullptr)
    {
        assert(false);
        return nullptr;
    }

    return m_d->GetSystemsManager();
}

} }