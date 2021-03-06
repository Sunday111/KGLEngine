#ifndef KGL_GRAPHICS_GRAPHIC_SYSTEM_H_INCLUDED
#define KGL_GRAPHICS_GRAPHIC_SYSTEM_H_INCLUDED

#include <KGL_Base/Ptr.h>
#include <KGL_Core/System.h>
#include <KGL_Graphics/Common.h>
#include <KGL_Graphics/Render/Shaders/ShaderProgram.h>

namespace KGL { namespace Graphics {

class WindowManager;

class KGL_GRAPHICS_API GraphicSystem : public Core::System
{
    DECLARE_CLASS_RTTI(GraphicSystem, Core::System)

public:
    GraphicSystem();
    ~GraphicSystem();

    bool Update() override;
    void AddShaderProgram(const Ptr<ShaderProgram>& shaderProgram);
    WindowManager* GetWindowManager();

private:
    class Impl;
    Impl* m_d;
};


} }

#endif