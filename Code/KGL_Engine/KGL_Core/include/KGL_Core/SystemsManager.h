#ifndef KGL_CORE_ISYSTEMS_MANAGER_H_INCLUDED
#define KGL_CORE_ISYSTEMS_MANAGER_H_INCLUDED

#include <KGL_Core/ISystem.h>
#include <memory>

namespace KGL { namespace Core {

class KGL_CORE_API SystemsManager :
    public Object
{
	DECLARE_SUPPORT_RTTI(SystemsManager, Object)

public:
	explicit SystemsManager();
	~SystemsManager();

	virtual bool RegisterSystem(std::unique_ptr<ISystem> system);
	virtual bool Update();

private:
	class Impl;
	Impl* m_d;
};

} }

#endif /*KGL_CORE_ISYSTEMS_MANAGER_H_INCLUDED*/