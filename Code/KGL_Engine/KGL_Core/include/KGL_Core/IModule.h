#ifndef KGL_CORE_IMODULE_H_INCLUDED
#define KGL_CORE_IMODULE_H_INCLUDED

#include <KGL_Core/Object.h>

namespace KGL { namespace Core {

class KGL_CORE_API IModule :
    public Object
{
public:
	virtual int GetModuleId() = 0;
};

KGL_CORE_API IModule* GetModule();

} }

#endif /* KGL_CORE_IMODULE_H_INCLUDED */