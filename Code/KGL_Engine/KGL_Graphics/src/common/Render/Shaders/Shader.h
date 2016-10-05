#ifndef KGL_GRAPHICS_SHADER_H_INCLUDED
#define KGL_GRAPHICS_SHADER_H_INCLUDED

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
class Shader
{
public:
    Shader(const Shader&) = delete;
    ~Shader();

    ShaderType GetShaderType() const { return m_type; }
    GLuint GetId() const { return m_id; }

    bool RecompileShaderWithCode(const char* code,
        std::ostream* logstream = nullptr);

protected:
    explicit Shader(ShaderType type, const char* fileName,
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

template<ShaderType shaderType>
class TShader : public Shader
{
public:
    explicit TShader(const char* fileName,
        const char* additionalCode = nullptr,
        std::ostream* logstream = nullptr) :
        Shader(shaderType, fileName, additionalCode, logstream)
    {}
};

using VertexShaderImpl = TShader<ShaderType::Vertex>;
using VertexShaderImplPtr = std::shared_ptr<VertexShaderImpl>;

using FragmentShaderImpl = TShader<ShaderType::Fragment>;
using FragmentShaderImplPtr = std::shared_ptr<FragmentShaderImpl>;

} }

#endif /*KGL_GRAPHICS_SHADER_H_INCLUDED*/