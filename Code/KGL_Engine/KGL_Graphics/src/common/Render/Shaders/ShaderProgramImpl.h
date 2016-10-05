#ifndef KGL_GRAPHICS_SHADER_PROGRAM_IMPL_H_INCLUDED
#define KGL_GRAPHICS_SHADER_PROGRAM_IMPL_H_INCLUDED

#include <Render/Shaders/Shader.h>

namespace KGL { namespace Graphics {

class ShaderProgramImpl
{
public:
    explicit ShaderProgramImpl(
        const VertexShaderImplPtr& vertexShader,
        const FragmentShaderImplPtr& fragmentShader,
        std::ostream* logstream = nullptr);

    ~ShaderProgramImpl();

    ShaderProgramImpl(const ShaderProgramImpl&) = delete;

    bool Use() const;

    GLuint GetUniformLocation(const GLchar* uniformName) const;
    GLuint TryGetUniformLocation(const GLchar* uniformName) const;

    void RecompileShaderWithText(ShaderType type, const char* addtionalCode);

    const VertexShaderImplPtr& GetVertexShader() const { return m_vertexShader; }

protected:
    bool Link(std::ostream* logstream = nullptr);

private:
    const GLuint m_id;
    VertexShaderImplPtr m_vertexShader;
    FragmentShaderImplPtr m_fragmentShader;
};

using ShaderProgramPtr = std::shared_ptr<ShaderProgramImpl>;

} }

#endif /* KGL_GRAPHICS_SHADER_PROGRAM_IMPL_H_INCLUDED */