#include <KGL_Core/ResourceManager.h>
#include <KGL_Core/TypeRegistry.h>
#include <KGL_Core/RTTI.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

DEFINE_CLASS_RTTI(KGL::Core::ResourceManager, KGL::Core::Object)

namespace KGL { namespace Core {

namespace
{

class Resource
{
public:
    Resource() {}

    explicit Resource(const char* path, const Ptr<Object>& obj) :
        m_path(path),
        m_object(obj)
    {}

    Resource(const Resource&) = delete;

    Resource(Resource&& uref) :
        m_path(std::move(uref.m_path)),
        m_object(std::move(uref.m_object))
    {}

    Ptr<Object> GetObject()
    {
        return m_object;
    }

    Resource& operator=(const Resource&) = delete;
    Resource& operator=(Resource&& uref)
    {
        assert(m_path != uref.m_path);

        m_path = std::move(uref.m_path);
        m_object = std::move(uref.m_object);

        return *this;
    }

    bool operator==(const Resource& ref)
    {
        return m_path == ref.m_path;
    }
    bool operator<(const Resource& ref)
    {
        return m_path < ref.m_path;
    }

    bool operator==(const char* path)
    {
        return std::strcmp(m_path.c_str(), path) == 0;
    }
    bool operator<(const char* path)
    {
        return std::lexicographical_compare(
            m_path.c_str(),
            m_path.c_str() + m_path.size(),
            path,
            path + std::strlen(path));
    }

    static Resource Create(const char* format)
    {
        Resource result;
        std::string line, tmp;

        const char* fileVarName = "file=\"";
        const char* sourceVar = std::strstr(format, fileVarName)
            + std::strlen(fileVarName);

        std::string path(sourceVar, std::strchr(sourceVar, '\"'));

        std::ifstream file(path);

        if (file.good())
        {
            if(std::getline(file, line))
            {
                std::istringstream iss(line);

                iss >> tmp;

                if (tmp == "Class")
                {
                    iss >> tmp;

                    auto types = TypeRegistry::GetInstance()->GetTypes();
                    const int typesCount = types.size();

                    for (int typeIndex = 0; typeIndex < typesCount; ++typeIndex)
                    {
                        auto& type = types[typeIndex];

                        if (!type.IsResource())
                        {
                            continue;
                        }

                        if (type.GetTypeTag() == tmp)
                        {
                            auto fn = type.GetCreateFromFileFn();

                            assert(fn != nullptr);

                            auto obj = fn(file);

                            if (obj != nullptr)
                            {
                                result = Resource(format, obj);
                                break;
                            }
                        }
                    }
                }
            }
        }

        return result;
    }

    bool Valid() const
    {
        return !m_path.empty()
            && m_object != nullptr;
    }

private:
    std::string m_path;
    Ptr<Object> m_object;
};

}

class ResourceManager::Impl
{
public:

    Resource* FindResource(const char* path)
    {
        for (auto& res : m_resources)
        {
            if (res == path)
            {
                return &res;
            }
        }

        return nullptr;
    }

    std::vector<Resource> m_resources;
};

ResourceManager::ResourceManager() :
    m_d(new Impl)
{}

ResourceManager::~ResourceManager()
{
    assert(m_d != nullptr);
    delete m_d;
}

Ptr<Object> ResourceManager::LoadResource(const char* format)
{
    assert(m_d != nullptr);

    auto res = m_d->FindResource(format);

    if (res != nullptr)
    {
        return res->GetObject();
    }

    Resource loaded = Resource::Create(format);

    if (!loaded.Valid())
    {
        return nullptr;
    }

    m_d->m_resources.push_back(std::move(loaded));

    return m_d->m_resources.back().GetObject();
}

} }