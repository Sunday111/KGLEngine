#ifndef KGL_GRAPHICS_MONITOR_MANAGER_H_INCLUDED
#define KGL_GRAPHICS_MONITOR_MANAGER_H_INCLUDED

#include <memory>
#include <KGL_Base/ArrayView.h>
#include <KGL_Graphics/Common.h>

namespace KGL { namespace Graphics {

class Monitor;

class KGL_GRAPHICS_API MonitorManager
{
public:
    explicit MonitorManager();
    explicit MonitorManager(const MonitorManager&) = delete;
    explicit MonitorManager(MonitorManager&& uref);
    ~MonitorManager();

    ArrayView<const std::unique_ptr<Monitor>> GetMonitors() const;

private:
    class Impl;
    Impl* m_d;
};

} }

#endif