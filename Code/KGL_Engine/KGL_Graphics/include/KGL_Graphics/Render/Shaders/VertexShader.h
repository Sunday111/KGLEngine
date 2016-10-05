#ifndef KGL_GRAPHICS_VERTEX_SHADER_H_INCLUDED
#define KGL_GRAPHICS_VERTEX_SHADER_H_INCLUDED

#include <KGL_Graphics/Common.h>
#include <memory>
#include <ostream>

namespace KGL { namespace Graphics {

class VertexShaderImpl;

class KGL_GRAPHICS_API VertexShader
{
public:
    explicit VertexShader(const char* fileName,
        const char* additionalCode = nullptr,
        std::ostream* logstream = nullptr);
    VertexShader(const VertexShader&) = delete;
    VertexShader(VertexShader&& uref);
    ~VertexShader();

    unsigned int GetId() const;
    bool RecompileShaderWithCode(const char* code,
        std::ostream* logstream = nullptr);

    VertexShader& operator=(const VertexShader&) = delete;
    VertexShader& operator=(VertexShader&& uref);

private:
    VertexShaderImpl* m_d;
};

using VertexShaderPtr = std::shared_ptr<VertexShader>;

} }

#endif /* KGL_GRAPHICS_VERTEX_SHADER_H_INCLUDED */