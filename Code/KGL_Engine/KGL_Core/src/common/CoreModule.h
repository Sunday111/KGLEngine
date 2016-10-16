#ifndef KGL_CORE_CORE_MODULE_H_INCLUDED
#define KGL_CORE_CORE_MODULE_H_INCLUDED

#include <KGL_Core/ICoreModule.h>

namespace KGL { namespace Core {

class CoreModule : public ICoreModule
{
public:
	int GetModuleId() override;
	int GetNextModuleId() override;

	static CoreModule* Instance();

private:
	CoreModule();

	int m_nextModuleId;
	int m_id;
};

} }

#endif /* KGL_CORE_CORE_MODULE_H_INCLUDED */