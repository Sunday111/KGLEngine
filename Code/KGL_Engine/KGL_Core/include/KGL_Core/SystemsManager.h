#ifndef KGL_CORE_SYSTEMS_MANAGER_H_INCLUDED
#define KGL_CORE_SYSTEMS_MANAGER_H_INCLUDED

#include <KGL_Core/Common.h>
#include <memory>

namespace KGL { namespace Core {

class System;
class SystemsManagerImpl;

class KGL_CORE_API SystemsManager
{
public:
    explicit SystemsManager();
    explicit SystemsManager(const SystemsManager&) = delete;
    explicit SystemsManager(SystemsManager&& uref);
    ~SystemsManager();

    bool RegisterSystem(std::unique_ptr<System> system);
    bool Update();

    SystemsManager& operator=(const SystemsManager&) = delete;
    SystemsManager& operator=(SystemsManager&&);

private:
    SystemsManagerImpl* m_d;
};

} }

#endif /*KGL_CORE_SYSTEMS_MANAGER_H_INCLUDED*/