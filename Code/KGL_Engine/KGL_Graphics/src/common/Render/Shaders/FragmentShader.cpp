#include <cassert>
#include <KGL_Graphics/Render/Shaders/FragmentShader.h>
#include "FragmentShaderImpl.h"

namespace KGL { namespace Graphics {

FragmentShader::FragmentShader(const char* fileName,
    const char* additionalCode, std::ostream* logstream) :
    m_d(new FragmentShaderImpl(fileName, additionalCode, logstream))
{}

FragmentShader::FragmentShader(FragmentShader&& uref) :
    m_d(uref.m_d)
{
    uref.m_d = nullptr;
}

FragmentShader::~FragmentShader()
{
    if (m_d != nullptr)
    {
        delete m_d;
    }
}

unsigned int FragmentShader::GetId() const
{
    assert(m_d != nullptr);
    return m_d->GetId();
}

bool FragmentShader::RecompileShaderWithCode(
    const char* code, std::ostream* logstream)
{
    assert(m_d != nullptr);
    return m_d->RecompileShaderWithCode(code, logstream);
}

FragmentShader& FragmentShader::operator=(FragmentShader&& uref)
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