#ifndef KGL_CORE_MODULE_H_INCLUDED
#define KGL_CORE_MODULE_H_INCLUDED

#include <KGL_Core/Object.h>

namespace KGL { namespace Core {

class KGL_CORE_API Module :
    public Object
{
public:
	virtual int GetModuleId() = 0;
};

} }

#endif