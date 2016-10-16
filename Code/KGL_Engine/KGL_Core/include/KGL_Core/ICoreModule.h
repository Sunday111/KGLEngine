#ifndef KGL_CORE_ICORE_MODULE_H_INCLUDED
#define KGL_CORE_ICORE_MODULE_H_INCLUDED

#include <KGL_Core/IModule.h>

namespace KGL { namespace Core {

class KGL_CORE_API ICoreModule : public IModule
{
public:
	/* Returns next module id and increments it */
	virtual int GetNextModuleId() = 0;
};

KGL_CORE_API ICoreModule* GetCoreModule();

} }

#endif /* KGL_CORE_ICORE_MODULE_H_INCLUDED */