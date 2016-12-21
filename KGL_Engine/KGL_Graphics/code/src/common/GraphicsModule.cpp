#include <KGL_Graphics/GraphicsModule.h>

DEFINE_CLASS_RTTI(KGL::Graphics::GraphicsModule, KGL::Core::Module)

namespace KGL { namespace Graphics {

class GraphicsModule::Impl
{
public:
    explicit Impl() :
        m_id(Core::CoreModule::GetInstance()->GetNextModuleId())
    {

    }

    const int m_id;
};


GraphicsModule::~GraphicsModule()
{
    assert(m_d != nullptr);
}

int GraphicsModule::GetModuleId()
{
    assert(m_d != nullptr);
    return m_d->m_id;
}

GraphicsModule* GraphicsModule::Instance()
{
    static GraphicsModule instance;
    return &instance;
}

GraphicsModule::GraphicsModule() :
    m_d(new Impl)
{}

} }