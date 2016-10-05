#include <cassert>
#include <KGL_Graphics/Render/Shaders/VertexShader.h>
#include "VertexShaderImpl.h"

namespace KGL { namespace Graphics {

VertexShader::VertexShader(const char* fileName,
    const char* additionalCode, std::ostream* logstream) :
    m_d(new VertexShaderImpl(fileName, additionalCode, logstream))
{}

VertexShader::VertexShader(VertexShader&& uref) :
    m_d(uref.m_d)
{
    uref.m_d = nullptr;
}

VertexShader::~VertexShader()
{
    if (m_d != nullptr)
    {
        delete m_d;
    }
}

unsigned int VertexShader::GetId() const
{
    assert(m_d != nullptr);
    return m_d->GetId();
}

bool VertexShader::RecompileShaderWithCode(
    const char* code, std::ostream* logstream)
{
    assert(m_d != nullptr);
    return m_d->RecompileShaderWithCode(code, logstream);
}

VertexShader& VertexShader::operator=(VertexShader&& uref)
{
    if (m_d != nullptr)
    {
        delete m_d;
    }

    m_d = uref.m_d;
    uref.m_d = nullptr;

    return *this;
}

} }