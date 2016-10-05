#include <cassert>

#include "Render/Shaders/ShaderProgramImpl.h"

namespace KGL { namespace Graphics {

ShaderProgramImpl::ShaderProgramImpl(const VertexShaderPtr& vertexShader,
    const FragmentShaderPtr& fragmentShader, std::ostream* logstream) :
m_id(glCreateProgram()),
m_vertexShader(vertexShader),
m_fragmentShader(fragmentShader)
{
    if (m_vertexShader != nullptr)
    {
        glAttachShader(m_id, vertexShader->GetId());
    }

    if (m_fragmentShader != nullptr)
    {
        glAttachShader(m_id, m_fragmentShader->GetId());
    }

    const bool linkRes = Link(logstream);
    assert(linkRes);
}

ShaderProgramImpl::~ShaderProgramImpl()
{
    glDeleteProgram(m_id);
}

bool ShaderProgramImpl::Use() const
{
    glUseProgram(m_id);
    return true;
}

GLuint ShaderProgramImpl::GetUniformLocation(const GLchar* uniformName) const
{
    const GLuint result = glGetUniformLocation(m_id, uniformName);
    assert(result != -1);
    return result;
}

GLuint ShaderProgramImpl::TryGetUniformLocation(const GLchar* uniformName) const
{
    const GLuint result = glGetUniformLocation(m_id, uniformName);
    return result;
}

void ShaderProgramImpl::RecompileShaderWithText(ShaderType type, const char* addtionalCode)
{
    switch (type)
    {
    case ShaderType::Vertex:
        m_vertexShader->RecompileShaderWithCode(addtionalCode);
        break;
    case ShaderType::Fragment:
        m_fragmentShader->RecompileShaderWithCode(addtionalCode);
        break;
    default:
        assert(!"Not implemented here");
        break;
    }
}

bool ShaderProgramImpl::Link(std::ostream* logstream)
{
    glLinkProgram(m_id);

    GLint success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);

    if (!success) {
        if (logstream != nullptr)
        {
            GLchar infoLog[512];
            glGetProgramInfoLog(m_id, 512, NULL, infoLog);
            *logstream << "ERROR::SHADER_PROGRAM::" << m_id
                << "::LINK_FAILED\n" << infoLog << std::endl;
        }

        return false;
    }

    return true;
}

} }