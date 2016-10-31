#ifndef RESOURCE_MANAGER_H_INCLUDED
#define RESOURCE_MANAGER_H_INCLUDED

#include <KGL_Base/Ptr.h>
#include <KGL_Core/Object.h>

namespace KGL { namespace Core {

class KGL_CORE_API ResourceManager : public Object
{
	DECLARE_CLASS_RTTI(ResourceManager, Object);

public:
	explicit ResourceManager();
	~ResourceManager();

	Ptr<Object> LoadResource(const char* path);

private:
	class Impl;
	Impl* m_d;
};

} }

#endif /* RESOURCE_MANAGER_H_INCLUDED */