#ifndef KGL_GRAPHICS_RENDER_CONTEXT_H_DEFINED
#define KGL_GRAPHICS_RENDER_CONTEXT_H_DEFINED

#include "KGL_Graphics/Object.h"

namespace KGL { namespace Graphics {

class RenderContextManager;
class RenderContextImpl;

class KGL_GRAPHICS_API RenderContext :
    public Object
{
    DECLARE_CLASS_RTTI(RenderContext, Object)

public:
    RenderContext(int id);
    RenderContext(const RenderContext&) = delete;
    RenderContext(RenderContext&& uref);
    ~RenderContext();

    RenderContextImpl* GetImpl() const { return m_d; }

    void MakeCurrent() const;
    bool ShouldClose() const;
    void SwapBuffers() const;
    int GetId() const;

private:

    RenderContextImpl* m_d;
};

} }

#endif