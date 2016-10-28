#include "KGL_Core/CreateInstance.h"
#include "Application.h"

namespace KGL { namespace Core {

template<>
typename InstanceCreator<KGL::Core::IApplication>::Pointer
InstanceCreator<KGL::Core::IApplication>::CreateInstance()
{
	return Ptr<IApplication>(new Application());
}

template class InstanceCreator<KGL::Core::IApplication>;

} }