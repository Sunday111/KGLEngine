#ifndef KGL_CORE_SYSTEMS_MANAGER_H_INCLUDED
#define KGL_CORE_SYSTEMS_MANAGER_H_INCLUDED

#include <KGL_Core/ISystemsManager.h>
#include <memory>
#include "Object.h"
#include <vector>

namespace KGL { namespace Core {

class SystemsManager :
    public virtual ISystemsManager,
    public virtual Object
{
public:
	bool RegisterSystem(std::unique_ptr<ISystem> system) override;
	bool Update() override;

    DECLARE_SUPPORT_RTTI(SystemsManager, Object)
private:
	std::vector<std::unique_ptr<ISystem>> m_systems;
};

} }

#endif /* KGL_CORE_SYSTEMS_MANAGER_H_INCLUDED */