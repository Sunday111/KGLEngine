#ifndef KGL_CORE_TYPE_REGISTRY_H_INCLUDED
#define KGL_CORE_TYPE_REGISTRY_H_INCLUDED

#include <KGL_Base/Ptr.h>
#include <KGL_Base/ArrayView.h>
#include <KGL_Core/Object.h>
#include <fstream>
#include <vector>

namespace KGL { namespace Core {

class KGL_CORE_API TypeInfo
{
public:
    using CreateFromFileFn = Ptr<Object>(*)(std::ifstream& filename);

    explicit TypeInfo(int id, CreateFromFileFn createFromFile,
        const char* tag, std::vector<int>&& parentTypes);

    TypeInfo(TypeInfo&& uref);

    TypeInfo(const TypeInfo&) = delete;

    const TypeInfo& operator=(TypeInfo&& uref);
    const TypeInfo& operator=(const TypeInfo& ref) = delete;

    bool IsResource() const;
    int TypeId() const;

    ArrayView<const int> ParentTypes() const;

    operator int() const;

    const char* GetTypeTag() const;

    CreateFromFileFn GetCreateFromFileFn() const;

private:
    class Impl;
    Impl* m_d;
};

class KGL_CORE_API TypeRegistry : public Object
{
    DECLARE_CLASS_RTTI(TypeRegistry, Object)

public:

    static TypeRegistry* GetInstance();

    ~TypeRegistry();

    bool TypeRegistered(int typeId) const;
    void RegisterType(int typeId, const char* typetag, TypeInfo::CreateFromFileFn createFromFile, std::vector<int>&& parents);
    bool IsTypeOf(int targetTypeId, int checkFor) const;
    int GetNextTypeId();
    ArrayView<const TypeInfo> GetTypes() const;
    const TypeInfo* GetTypeById(int id) const;

protected:
    explicit TypeRegistry();

private:
    class Impl;
    Impl* m_d;
};

} }


#endif