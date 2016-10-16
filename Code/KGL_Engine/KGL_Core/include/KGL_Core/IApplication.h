#ifndef KGL_CORE_IAPPLICATION_H_INCLUDED
#define KGL_CORE_IAPPLICATION_H_INCLUDED

#include <KGL_Core/IObject.h>

namespace KGL { namespace Core {

class KGL_CORE_API IApplicationListener : public IObject
{
public:
	virtual void OnInitialize(IApplication*) = 0;
};

class ISystemsManager;

class KGL_CORE_API IApplication : public IObject
{
public:
	/* Update all systems of application
	* Return false if need exit of application failed
	*/
	virtual bool Update() = 0;

	/* Add application listener
	 * Returns false if such a listener is already added
	 * If boo variable is true, Application will delete listener in destructor
	 */
	virtual bool AddListener(IApplicationListener* listener, bool destroy) = 0;

	virtual ISystemsManager* GetSystemsManager() = 0;

	virtual void Initialize() = 0;
};

} }

#endif /* KGL_CORE_IAPPLICATION_H_INCLUDED */