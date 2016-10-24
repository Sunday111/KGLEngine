#ifndef KGL_CORE_APPLICATION_H_INCLUDED
#define KGL_CORE_APPLICATION_H_INCLUDED

#include <memory>
#include <vector>

#include <KGL_Core/IApplication.h>
#include "Object.h"
#include <KGL_Core/RTTI.h>

namespace KGL { namespace Core {

class ISystemsManager;

class Application :
	public virtual IApplication,
	public virtual Object
{
public:
    explicit Application();
    ~Application();

	ISystemsManager* GetSystemsManager() override;
	bool Update() override;
	bool AddListener(IApplicationListener* listener, bool destroy) override;
	void Initialize() override;

    DECLARE_SUPPORT_RTTI(Application, Object)

private:
	std::vector<std::pair<bool,IApplicationListener*>> m_listeners;
    std::unique_ptr<ISystemsManager>  m_systemsManager;
};

} }

#endif /*KGL_CORE_APPLICATION_H_INCLUDED*/