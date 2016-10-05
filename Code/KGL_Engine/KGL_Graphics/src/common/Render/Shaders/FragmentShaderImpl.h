#ifndef KGL_GRAPHICS_FRAGMENT_SHADER_IMPL_H_INCLUDED
#define KGL_GRAPHICS_FRAGMENT_SHADER_IMPL_H_INCLUDED

#include "ShaderImpl.h"

namespace KGL { namespace Graphics {

class FragmentShaderImpl : public ShaderImpl
{
public:
    explicit FragmentShaderImpl(const char* fileName,
        const char* additionalCode = nullptr,
        std::ostream* logstream = nullptr);
};

} }

#endif /* KGL_GRAPHICS_FRAGMENT_SHADER_IMPL_H_INCLUDED */