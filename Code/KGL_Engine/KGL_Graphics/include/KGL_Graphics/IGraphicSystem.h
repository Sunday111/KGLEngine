#ifndef KGL_GRAPHICS_IGRAPHIC_SYSTEM_H_INCLUDED
#define KGL_GRAPHICS_IGRAPHIC_SYSTEM_H_INCLUDED

#include <KGL_Core/System.h>
#include <KGL_Graphics/Common.h>
#include <KGL_Graphics/Render/Shaders/IShaderProgram.h>

namespace KGL { namespace Graphics {

class WindowManager;

class KGL_GRAPHICS_API IGraphicSystem : public Core::System
{
public:
    virtual void AddShaderProgram(std::unique_ptr<IShaderProgram> shaderProgram) = 0;
    virtual WindowManager* GetWindowManager() = 0;
};


} }

#endif /* KGL_GRAPHICS_IGRAPHIC_SYSTEM_H_INCLUDED */