#ifndef KGL_CORE_SYSTEMS_MANAGER_IMPL_H_INCLUDED
#define KGL_CORE_SYSTEMS_MANAGER_IMPL_H_INCLUDED

#include <KGL_Core/Common.h>
#include <KGL_Core/System.h>
#include <memory>
#include <vector>

namespace KGL { namespace Core {

//class System;

class SystemsManagerImpl
{
public:
    explicit SystemsManagerImpl();
    ~SystemsManagerImpl();

    bool RegisterSystem(std::unique_ptr<System> system);
    bool Update();

private:
    std::vector<std::unique_ptr<System>> m_systems;
};

} }

#endif /*KGL_CORE_SYSTEMS_MANAGER_IMPL_H_INCLUDED*/