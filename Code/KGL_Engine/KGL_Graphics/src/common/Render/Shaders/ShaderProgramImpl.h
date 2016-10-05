#ifndef KGL_GRAPHICS_SHADER_PROGRAM_IMPL_H_INCLUDED
#define KGL_GRAPHICS_SHADER_PROGRAM_IMPL_H_INCLUDED

#include "ShaderImpl.h"
#include <KGL_Graphics/Render/Shaders/VertexShader.h>
#include <KGL_Graphics/Render/Shaders/FragmentShader.h>

namespace KGL { namespace Graphics {

class ShaderProgramImpl
{
public:
    explicit ShaderProgramImpl(
        const VertexShaderPtr& vertexShader,
        const FragmentShaderPtr& fragmentShader,
        std::ostream* logstream = nullptr);

    ~ShaderProgramImpl();

    ShaderProgramImpl(const ShaderProgramImpl&) = delete;

    bool Use() const;

    GLuint GetUniformLocation(const GLchar* uniformName) const;
    GLuint TryGetUniformLocation(const GLchar* uniformName) const;

    void RecompileShaderWithText(ShaderType type, const char* addtionalCode);

    const VertexShaderPtr& GetVertexShader() const { return m_vertexShader; }

protected:
    bool Link(std::ostream* logstream = nullptr);

private:
    const GLuint m_id;
    VertexShaderPtr m_vertexShader;
    FragmentShaderPtr m_fragmentShader;
};

using ShaderProgramPtr = std::shared_ptr<ShaderProgramImpl>;

} }

#endif /* KGL_GRAPHICS_SHADER_PROGRAM_IMPL_H_INCLUDED */