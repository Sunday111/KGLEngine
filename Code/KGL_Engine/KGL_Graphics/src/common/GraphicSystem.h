#ifndef KGL_GRAPHIC_SYSTEM_INCLUDED
#define KGL_GRAPHIC_SYSTEM_INCLUDED

#include <KGL_Core/RTTI.h>
#include <KGL_Graphics/IGraphicSystem.h>
#include <KGL_Graphics/Render/Shaders/IShaderProgram.h>
#include <KGL_Graphics/WindowManager.h>
#include <vector>

#include "Object.h"

namespace KGL { namespace Graphics {

class WindowManager;

class GraphicSystem :
    public virtual IGraphicSystem,
    public virtual Graphics::Object
{
public:
    explicit GraphicSystem();
    ~GraphicSystem();

    bool Update() override;
    void AddShaderProgram(std::unique_ptr<IShaderProgram> shaderProgram) override;
    WindowManager* GetWindowManager() override { return &m_windowManager; }

    DECLARE_SUPPORT_RTTI(GraphicSystem, Graphics::Object)
private:
    WindowManager m_windowManager;
    std::vector<std::unique_ptr<IShaderProgram>> m_shaderPrograms;
};

}}

#endif /*KGL_GRAPHIC_SYSTEM_INCLUDED*/