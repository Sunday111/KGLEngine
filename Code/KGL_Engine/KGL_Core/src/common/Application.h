#ifndef KGL_CORE_APPLICATION_H_INCLUDED
#define KGL_CORE_APPLICATION_H_INCLUDED

#include <memory>
#include <vector>

#include <KGL_Core/IApplication.h>
#include "Object.h"

namespace KGL { namespace Core {

class SystemsManager;

class Application :
	public virtual IApplication,
	public virtual Object
{
public:
    explicit Application();
    ~Application();

    SystemsManager* GetSystemsManager();
	bool Update() override;
	bool AddListener(IApplicationListener* listener, bool destroy) override;
	void Initialize() override;

private:
	std::vector<std::pair<bool,IApplicationListener*>> m_listeners;
    std::unique_ptr<SystemsManager>  m_systemsManager;
};

} }

#endif /*KGL_CORE_APPLICATION_H_INCLUDED*/