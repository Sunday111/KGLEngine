#ifndef KGL_GRAPHIC_SYSTEM_INCLUDED
#define KGL_GRAPHIC_SYSTEM_INCLUDED

#include <KGL_Graphics/Common.h>

namespace KGL { namespace Graphics {

class KGL_GRAPHICS_API GraphicSystem
{
public:
    explicit GraphicSystem();
    GraphicSystem(const GraphicSystem&) = delete;
    GraphicSystem(GraphicSystem&&);
    ~GraphicSystem();

private:
    class GraphicSystemImpl;
    const GraphicSystemImpl* m_d;
};

}}

#endif /*KGL_GRAPHIC_SYSTEM_INCLUDED*/