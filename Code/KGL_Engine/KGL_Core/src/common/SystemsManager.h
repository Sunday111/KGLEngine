#ifndef KGL_CORE_SYSTEMS_MANAGER_H_INCLUDED
#define KGL_CORE_SYSTEMS_MANAGER_H_INCLUDED

#include <KGL_Core/ISystemsManager.h>
#include <memory>
#include <vector>

namespace KGL { namespace Core {

class SystemsManager : public ISystemsManager
{
public:
	bool RegisterSystem(std::unique_ptr<ISystem> system) override;
	bool Update() override;

private:
	std::vector<std::unique_ptr<ISystem>> m_systems;
};

} }

#endif /* KGL_CORE_SYSTEMS_MANAGER_H_INCLUDED */