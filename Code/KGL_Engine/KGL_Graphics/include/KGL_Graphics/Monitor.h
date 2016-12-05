#ifndef KGL_GRAPHICS_MONITOR_H_INCLUDED
#define KGL_GRAPHICS_MONITOR_H_INCLUDED

#include <KGL_Graphics/Common.h>

namespace KGL { namespace Graphics {

class Monitor
{
public:
    ~Monitor();

private:
    class Impl;
    friend class MonitorManager;

    explicit Monitor(Impl* p);

    Impl* m_d;
};

} }

#endif