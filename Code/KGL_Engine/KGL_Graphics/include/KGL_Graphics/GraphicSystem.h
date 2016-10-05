#ifndef KGL_GRAPHIC_SYSTEM_INCLUDED
#define KGL_GRAPHIC_SYSTEM_INCLUDED

#include <KGL_Core/System.h>
#include <KGL_Graphics/Common.h>
#include <KGL_Graphics/Render/Shaders/ShaderProgram.h>

namespace KGL { namespace Graphics {

class WindowManager;

class KGL_GRAPHICS_API GraphicSystem : public Core::System
{
public:
    explicit GraphicSystem();
    GraphicSystem(const GraphicSystem&) = delete;
    GraphicSystem(GraphicSystem&&);
    ~GraphicSystem();

    bool Update() override;

    void AddShaderProgram(std::unique_ptr<ShaderProgram> shaderProgram);

    WindowManager* GetWindowManager();

private:
    class GraphicSystemImpl;
    GraphicSystemImpl* m_d;
};

}}

#endif /*KGL_GRAPHIC_SYSTEM_INCLUDED*/