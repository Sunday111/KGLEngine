#include <cassert>
#include <KGL_Base/Marco.h>
#include <KGL_Graphics/Render/Shaders/ShaderProgram.h>
#include <Render/Shaders/ShaderProgramImpl.h>

namespace KGL { namespace Graphics {

ShaderProgram::ShaderProgram(
    const VertexShaderPtr& vs,
    const FragmentShaderPtr& fs,
    std::ostream* logstream) :
    m_d(new ShaderProgramImpl(vs, fs, logstream))
{}

ShaderProgram::ShaderProgram(ShaderProgram&& uref) :
    m_d(uref.m_d)
{
    uref.m_d = nullptr;
}

ShaderProgram::~ShaderProgram()
{
    SAFE_DELETE(m_d);
}

bool ShaderProgram::Use() const
{
    assert(m_d != nullptr);
    return m_d->Use();
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& uref)
{
    SAFE_DELETE(m_d);
    m_d = uref.m_d;
    uref.m_d = nullptr;

    return *this;
}

} }