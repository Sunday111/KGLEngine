#ifndef KGL_GRAPHIC_SYSTEM_INCLUDED
#define KGL_GRAPHIC_SYSTEM_INCLUDED

#include <KGL_Graphics/Common.h>

namespace KGL { namespace Graphics {

class WindowManager;

class KGL_GRAPHICS_API GraphicSystem
{
public:
    explicit GraphicSystem();
    GraphicSystem(const GraphicSystem&) = delete;
    GraphicSystem(GraphicSystem&&);
    ~GraphicSystem();

    void Update();

    WindowManager* GetWindowManager();

private:
    class GraphicSystemImpl;
    GraphicSystemImpl* m_d;
};

}}

#endif /*KGL_GRAPHIC_SYSTEM_INCLUDED*/