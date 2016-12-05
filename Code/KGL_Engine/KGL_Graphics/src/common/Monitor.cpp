#include <KGL_Base/Marco.h>
#include <KGL_Graphics/Monitor.h>
#include "MonitorImpl.h"

namespace KGL { namespace Graphics {

Monitor::Monitor(Impl* p) :
    m_d(p)
{
    assert(p != nullptr);
}

Monitor::~Monitor()
{
    SAFE_DELETE(m_d);
}

} }