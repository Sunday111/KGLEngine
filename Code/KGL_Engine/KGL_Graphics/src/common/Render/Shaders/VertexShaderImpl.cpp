#include "VertexShaderImpl.h"

namespace KGL { namespace Graphics {

VertexShaderImpl::VertexShaderImpl(const char* fileName,
    const char* additionalCode, std::ostream* logstream) :
    ShaderImpl(ShaderType::Vertex, fileName, additionalCode, logstream)
{}

} }