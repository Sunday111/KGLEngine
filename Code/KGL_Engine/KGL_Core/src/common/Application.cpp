#include <KGL_Core/Application.h>
#include "ApplicationImpl.h"

namespace KGL { namespace Core {

Application::Application() :
    m_d(new ApplicationImpl())
{}

Application::Application(Application&& uref) :
    m_d(uref.m_d)
{
    uref.m_d = nullptr;
}

Application::~Application()
{
    if (m_d != nullptr)
    {
        delete m_d;
    }
}

Application& Application::operator=(Application&& uref)
{
    if (m_d != nullptr)
    {
        delete m_d;
    }

    m_d = uref.m_d;
    uref.m_d = nullptr;

    return *this;
}

} }