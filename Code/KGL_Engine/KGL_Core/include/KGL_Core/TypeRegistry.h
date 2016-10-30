#ifndef KGL_CORE_ITYPE_REGISTRY_H_INCLUDED
#define KGL_CORE_ITYPE_REGISTRY_H_INCLUDED

#include <KGL_Core/Object.h>
#include <vector>

namespace KGL { namespace Core {

class KGL_CORE_API TypeRegistry : public Object
{
	DECLARE_SUPPORT_RTTI(TypeRegistry, Object)

public:
	static TypeRegistry* GetInstance();

	~TypeRegistry();

    virtual bool TypeRegistered(int typeId) const;
    virtual void RegisterType(int typeId, std::vector<int>&& parents);
    virtual bool IsTypeOf(int targetTypeId, int checkFor) const;
    virtual int GetNextTypeId();

protected:
	explicit TypeRegistry();

private:
	class Impl;
	Impl* m_d;
};

} }


#endif /*KGL_CORE_ITYPE_REGISTRY__H_INCLUDED*/