#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <KGL_Core\Object.h>

namespace KGL { namespace Core {

class ApplicationListener;
class SystemsManager;

class KGL_CORE_API Application :
	public Object
{
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
	virtual bool AddListener(ApplicationListener* listener, bool destroy);

	virtual SystemsManager* GetSystemsManager();

	virtual void Initialize();

	DECLARE_SUPPORT_RTTI(Application, Object)

private:
	class Impl;
	Impl* m_d;
};

} }

#endif