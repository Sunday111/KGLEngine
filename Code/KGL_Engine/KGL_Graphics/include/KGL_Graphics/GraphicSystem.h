#ifndef KGL_GRAPHIC_SYSTEM_INCLUDED
#define KGL_GRAPHIC_SYSTEM_INCLUDED

#include <KGL_Core/ISystem.h>
#include <KGL_Graphics/Common.h>
#include <KGL_Graphics/Render/Shaders/IShaderProgram.h>

namespace KGL { namespace Graphics {

class WindowManager;

class KGL_GRAPHICS_API GraphicSystem : public Core::ISystem
{
public:
    explicit GraphicSystem();
    GraphicSystem(const GraphicSystem&) = delete;
    GraphicSystem(GraphicSystem&&);
    ~GraphicSystem();

    bool Update() override;

    void AddShaderProgram(std::unique_ptr<IShaderProgram> shaderProgram);

    WindowManager* GetWindowManager();

private:
    class GraphicSystemImpl;
    GraphicSystemImpl* m_d;
};

}}

#endif /*KGL_GRAPHIC_SYSTEM_INCLUDED*/