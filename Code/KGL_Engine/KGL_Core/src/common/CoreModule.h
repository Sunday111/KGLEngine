#ifndef KGL_CORE_CORE_MODULE_H_INCLUDED
#define KGL_CORE_CORE_MODULE_H_INCLUDED

#include <KGL_Core/ICoreModule.h>
#include <KGL_Core/RTTI.h>

#include "Object.h"

namespace KGL { namespace Core {

class CoreModule :
    public virtual ICoreModule,
    public virtual Object
{
public:

	int GetModuleId() override;
	int GetNextModuleId() override;

	static CoreModule* Instance();

    DECLARE_SUPPORT_RTTI(CoreModule, Object)

private:
	CoreModule();

	int m_nextModuleId;
	int m_id;
};

} }

#endif /* KGL_CORE_CORE_MODULE_H_INCLUDED */