#include <KGL_Base/Marco.h>
#include <KGL_Graphics/Monitor.h>
#include <KGL_Graphics/MonitorManager.h>
#include <vector>
#include "MonitorImpl.h"

namespace KGL { namespace Graphics {

class MonitorManager::Impl
{
public:

    Impl()
    {
        glfwSetMonitorCallback(Impl::MonitorCallback);

        int cnt;
        GLFWmonitor** ptrs = glfwGetMonitors(&cnt);

        monitors.reserve(cnt);

        while (cnt-- > 0)
        {
            std::unique_ptr<Monitor> p;
            p.reset(new Monitor(new Monitor::Impl(ptrs[cnt])));
            monitors.push_back(std::move(p));
        }
    }

    static void MonitorCallback(GLFWmonitor*, int event)
    {
        switch (event)
        {
            case GLFW_CONNECTED:
                assert(false);
                break;
            case GLFW_DISCONNECTED:
                assert(false);
                break;
        }
    }

    std::vector<std::unique_ptr<Monitor>> monitors;
};

MonitorManager::MonitorManager() :
    m_d(new Impl)
{}

MonitorManager::MonitorManager(MonitorManager&& uref) :
    m_d(uref.m_d)
{
    uref.m_d = nullptr;
}

MonitorManager::~MonitorManager()
{
    SAFE_DELETE(m_d);
}

ArrayView<const std::unique_ptr<Monitor>> MonitorManager::GetMonitors() const
{
    assert(m_d != nullptr);
    return MakeArrayView(m_d->monitors);
}

} }