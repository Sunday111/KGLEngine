#include <cassert>
#include <KGL_Core/SystemsManager.h>
#include "SystemsManagerImpl.h"

namespace KGL { namespace Core {

SystemsManager::SystemsManager() :
    m_d(new SystemsManagerImpl())
{}

SystemsManager::SystemsManager(SystemsManager&& uref) :
    m_d(uref.m_d)
{
    uref.m_d = nullptr;
}

SystemsManager::~SystemsManager()
{
    if (m_d != nullptr)
    {
        delete m_d;
    }
}

bool SystemsManager::RegisterSystem(std::unique_ptr<System> system)
{
    if (m_d == nullptr)
    {
        assert(false);
        return false;
    }

    return m_d->RegisterSystem(std::move(system));
}

bool SystemsManager::Update()
{
    assert(m_d != nullptr);
    return m_d->Update();
}

SystemsManager& SystemsManager::operator=(SystemsManager&& uref)
{
    assert(m_d == nullptr);
    m_d = uref.m_d;
    uref.m_d = nullptr;
    return *this;
}

} }