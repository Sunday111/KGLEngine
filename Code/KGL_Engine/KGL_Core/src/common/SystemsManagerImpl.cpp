#include "SystemsManagerImpl.h"

namespace KGL { namespace Core {

SystemsManagerImpl::SystemsManagerImpl() = default;
SystemsManagerImpl::~SystemsManagerImpl() = default;

bool SystemsManagerImpl::RegisterSystem(std::unique_ptr<System> system)
{
    m_systems.push_back(std::move(system));
    return true;
}

bool SystemsManagerImpl::Update()
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