#ifndef KGL_CORE_APPLICATION_H_INCLUDED
#define KGL_CORE_APPLICATION_H_INCLUDED

#include <KGL_Core/Common.h>

namespace KGL { namespace Core {

class ApplicationImpl;

class KGL_CORE_API Application
{
public:
    explicit Application();
    Application(const Application&) = delete;
    Application(Application&& uref);
    ~Application();

    Application& operator=(const Application&) = delete;
    Application& operator=(Application&& uref);

private:
    ApplicationImpl* m_d;
};

} }

#endif /*KGL_CORE_APPLICATION_H_INCLUDED*/