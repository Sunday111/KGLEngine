#ifndef KGL_CORE_APPLICATION_IMPL_H_INCLUDED
#define KGL_CORE_APPLICATION_IMPL_H_INCLUDED

#include <memory>

namespace KGL { namespace Core {

class SystemsManager;

class ApplicationImpl
{
public:
    explicit ApplicationImpl();
    ~ApplicationImpl();

    SystemsManager* GetSystemsManager();

private:
    std::unique_ptr<SystemsManager>  m_systemsManager;
};

} }

#endif /*KGL_CORE_APPLICATION_IMPL_H_INCLUDED*/