#ifndef KGL_GRAPHICS_VERTEX_SHADER_IMPL_H_INCLUDED
#define KGL_GRAPHICS_VERTEX_SHADER_IMPL_H_INCLUDED

#include "ShaderImpl.h"

namespace KGL { namespace Graphics {

class VertexShaderImpl : public ShaderImpl
{
public:
    explicit VertexShaderImpl(const char* fileName,
        const char* additionalCode = nullptr,
        std::ostream* logstream = nullptr);
};

} }

#endif