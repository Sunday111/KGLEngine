#ifndef KGL_GRAPHICS_GRAPHICS_MODULE_H_INCLUDED
#define KGL_GRAPHICS_GRAPHICS_MODULE_H_INCLUDED

#include <KGL_Core/CoreModule.h>
#include <KGL_Core/RTTI.h>
#include <KGL_Graphics/Object.h>

namespace KGL { namespace Graphics {

class GraphicsModule : public Core::Module
{
public:
    ~GraphicsModule();

    int GetModuleId() override;
    static GraphicsModule* Instance();

    DECLARE_CLASS_RTTI(GraphicsModule, Core::Module)
private:
    GraphicsModule();

    class Impl;
    Impl* m_d;
};

} }

#endif