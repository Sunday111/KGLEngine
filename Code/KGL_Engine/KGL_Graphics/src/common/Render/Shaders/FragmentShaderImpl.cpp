#include "FragmentShaderImpl.h"

namespace KGL { namespace Graphics {

FragmentShaderImpl::FragmentShaderImpl(const char* fileName,
    const char* additionalCode, std::ostream* logstream) :
    ShaderImpl(ShaderType::Fragment, fileName, additionalCode, logstream)
{}

} }