#ifndef KGL_CORE_ISYSTEMS_MANAGER_H_INCLUDED
#define KGL_CORE_ISYSTEMS_MANAGER_H_INCLUDED

#include <KGL_Core/ISystem.h>
#include <memory>

namespace KGL { namespace Core {

class KGL_CORE_API ISystemsManager :
    public IObject
{
public:
	virtual bool RegisterSystem(std::unique_ptr<ISystem> system) = 0;
	virtual bool Update() = 0;
};

} }

#endif /*KGL_CORE_ISYSTEMS_MANAGER_H_INCLUDED*/