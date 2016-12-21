#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <KGL_Core\Object.h>

namespace KGL { namespace Core {

class ApplicationListener;
class ResourceManager;
class SystemsManager;

class KGL_CORE_API Application :
	public Object
{
	DECLARE_CLASS_RTTI(Application, Object)

public:
	explicit Application();
	~Application();

	/* Update all systems of application
	* Return false if need exit of application failed
	*/
	virtual bool Update();

	/* Add application listener
	* Returns false if such a listener is already added
	* If boo variable is true, Application will delete listener in destructor
	*/
	bool AddListener(ApplicationListener* listener, bool destroy);

	SystemsManager* GetSystemsManager();

	ResourceManager* GetResouceManager();

	void Initialize();


private:
	class Impl;
	Impl* m_d;
};

} }

#endif