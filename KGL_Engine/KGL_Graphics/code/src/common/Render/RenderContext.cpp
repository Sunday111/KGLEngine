#include <KGL_Base/Marco.h>
#include <KGL_Graphics/Render/RenderContext.h>
#include "RenderContextImpl.h"

DEFINE_CLASS_RTTI(KGL::Graphics::RenderContext, KGL::Graphics::Object)

namespace KGL { namespace Graphics {

void RenderContext::MakeCurrent() const
{
    assert(m_d != nullptr);
    glfwMakeContextCurrent(m_d->wnd);
}

bool RenderContext::ShouldClose() const
{
    assert(m_d != nullptr);
    return glfwWindowShouldClose(m_d->wnd) != 0;
}

void RenderContext::SwapBuffers() const
{
    assert(m_d != nullptr);
    glfwSwapBuffers(m_d->wnd);
}

int RenderContext::GetId() const
{
    return m_d->id;
}

RenderContext::RenderContext(int id) :
    m_d(new RenderContextImpl(id))
{}

RenderContext::RenderContext(RenderContext&& uref) :
    m_d(uref.m_d)
{
    uref.m_d = nullptr;
}

RenderContext::~RenderContext()
{
    SafeDelete(m_d);
}

} }