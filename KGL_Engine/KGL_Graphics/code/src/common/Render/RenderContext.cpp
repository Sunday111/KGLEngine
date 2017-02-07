#include <KGL_Base/Marco.h>
#include <KGL_Graphics/Render/RenderContext.h>

DEFINE_CLASS_RTTI(KGL::Graphics::RenderContext, KGL::Graphics::Object)

namespace KGL { namespace Graphics {

class RenderContextImpl
{
public:
    int contextId;
};

int RenderContext::GetId() const
{
    assert(m_d != nullptr);
    return m_d->contextId;
}

RenderContext::RenderContext(int id) :
    m_d(new RenderContextImpl)
{
    m_d->contextId = id;
}

RenderContext::RenderContext(RenderContext&& uref) :
    m_d(uref.m_d)
{
    uref.m_d = nullptr;
}

RenderContext::~RenderContext()
{
    SAFE_DELETE(m_d);
}

} }