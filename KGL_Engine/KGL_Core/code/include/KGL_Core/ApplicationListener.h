#ifndef KGL_CORE_APPLICATION_LISTENER
#define KGL_CORE_APPLICATION_LISTENER

#include <KGL_Core/Object.h>

namespace KGL { namespace Core {

class Application;

class KGL_CORE_API ApplicationListener
{
public:
	virtual void OnInitialize(Application*) = 0;
	virtual ~ApplicationListener() = default;
};

} }

#endif