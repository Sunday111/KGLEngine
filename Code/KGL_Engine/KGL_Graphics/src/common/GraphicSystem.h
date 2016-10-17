#ifndef KGL_GRAPHIC_SYSTEM_INCLUDED
#define KGL_GRAPHIC_SYSTEM_INCLUDED

#include <KGL_Graphics/IGraphicSystem.h>
#include <KGL_Graphics/Render/Shaders/IShaderProgram.h>
#include <KGL_Graphics/WindowManager.h>
#include <vector>


namespace KGL { namespace Graphics {

class WindowManager;

class GraphicSystem :
    public IGraphicSystem
{
public:
    explicit GraphicSystem();
    ~GraphicSystem();

    bool Update() override;

    void AddShaderProgram(std::unique_ptr<IShaderProgram> shaderProgram) override;

    WindowManager* GetWindowManager() override { return &m_windowManager; }

private:
    WindowManager m_windowManager;
    std::vector<std::unique_ptr<IShaderProgram>> m_shaderPrograms;
};

}}

#endif /*KGL_GRAPHIC_SYSTEM_INCLUDED*/