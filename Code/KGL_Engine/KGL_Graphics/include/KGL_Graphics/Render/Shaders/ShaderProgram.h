#ifndef KGL_GRAPHICS_SHADER_PROGRAM_H_INCLUDED
#define KGL_GRAPHICS_SHADER_PROGRAM_H_INCLUDED

#include <KGL_Graphics/Common.h>
#include <KGL_Graphics/Render/Shaders/FragmentShader.h>
#include <KGL_Graphics/Render/Shaders/VertexShader.h>
#include <memory>

namespace KGL { namespace Graphics {

class ShaderProgramImpl;

class KGL_GRAPHICS_API ShaderProgram
{
public:
    explicit ShaderProgram(
        const VertexShaderPtr& vs,
        const FragmentShaderPtr& fs,
        std::ostream* logstream = nullptr);
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram(ShaderProgram&& uref);
    ~ShaderProgram();

    bool Use() const;

    ShaderProgram& operator=(const ShaderProgram&) = delete;
    ShaderProgram& operator=(ShaderProgram&& uref);

private:
    ShaderProgramImpl* m_d;
};

using ShaderProgramPtr = std::shared_ptr<ShaderProgram>;

} }

#endif /* KGL_GRAPHICS_SHADER_PROGRAM_H_INCLUDED */