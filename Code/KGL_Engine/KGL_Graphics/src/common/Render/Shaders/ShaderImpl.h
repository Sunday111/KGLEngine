#ifndef KGL_GRAPHICS_SHADER_IMPL_H_INCLUDED
#define KGL_GRAPHICS_SHADER_IMPL_H_INCLUDED

#include <memory>

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include <ostream>

#include <KGL_Graphics/Render/Shaders/ShaderType.h>

namespace KGL { namespace Graphics {

//This is the base class for shader
class ShaderImpl
{
public:
    ShaderImpl(const ShaderImpl&) = delete;
    ~ShaderImpl();

    ShaderType GetShaderType() const { return m_type; }
    GLuint GetId() const { return m_id; }

    bool RecompileShaderWithCode(const char* code,
        std::ostream* logstream = nullptr);

protected:
    explicit ShaderImpl(ShaderType type, const char* fileName,
        const char* additionalCode = nullptr,
        std::ostream* logstream = nullptr);

    bool Compile(const char* fileName,
        const char* additionalCode = nullptr,
        std::ostream* logstream = nullptr);

private:
    const ShaderType m_type;
    const GLuint m_id;
    std::string m_code;
};

} }

#endif /*KGL_GRAPHICS_SHADER_IMPL_H_INCLUDED*/