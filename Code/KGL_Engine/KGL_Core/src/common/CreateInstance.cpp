#include "KGL_Core/CreateInstance.h"
#include "Application.h"

namespace KGL { namespace Core {

void CreateInstance(IApplicationPtr& p)
{
	IApplicationPtr::NoAddRef noAddRef;
    p = IApplicationPtr(new Application(), noAddRef);
}

} }