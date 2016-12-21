#include <KGL_Base/UnusedVar.h>
#include <KGL_Core/RTTI.h>
#include <KGL_Core/TypeRegistry.h>
#include <KGL_Graphics/Render/Shaders/Shader.h>
#include <cassert>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#define INSTANTIATE_SHADER(shaderType) \
    DEFINE_CLASS_RTTI(KGL::Graphics::Shader<shaderType>, KGL::Graphics::Object) \
    template class KGL::Graphics::Shader<shaderType>

INSTANTIATE_SHADER(KGL::Graphics::ShaderType::Vertex);
INSTANTIATE_SHADER(KGL::Graphics::ShaderType::Fragment);

namespace KGL { namespace Graphics { namespace {

template<ShaderType shaderType>
class ShaderTypeHelper;

template<>
class ShaderTypeHelper<ShaderType::Vertex>
{
public:
    enum
    {
        GL_ShaderType = GL_VERTEX_SHADER
    };

    static const char* GetName()
    {
        return "Vertex";
    }
};

template<>
class ShaderTypeHelper<ShaderType::Fragment>
{
public:
    enum
    {
        GL_ShaderType = GL_FRAGMENT_SHADER
    };

    static const char* GetName()
    {
        return "Fragment";
    }
};

}

template<ShaderType shaderType>
class Shader<shaderType>::Impl
{
public:
    Impl() :
        m_id(glCreateShader(ShaderTypeHelper<shaderType>::GL_ShaderType))
    {}

    ~Impl()
    {
        glDeleteShader(m_id);
    }

    const int m_id;
    std::string m_code;
};

template<ShaderType shaderType>
Shader<shaderType>::Shader() :
    m_d(new Impl)
{}

template<ShaderType shaderType>
Shader<shaderType>::~Shader()
{
    assert(m_d != nullptr);
    delete m_d;
}

template<ShaderType shaderType>
bool Shader<shaderType>::RecompileShaderWithCode(const char* code, std::ostream* logstream)
{
    assert(m_d != nullptr && code != nullptr);

    const char * codePointers[2]
    {
        code,
        m_d->m_code.data()
    };

    glShaderSource(m_d->m_id, 2, codePointers, NULL);
    glCompileShader(m_d->m_id);

    GLint success;
    glGetShaderiv(m_d->m_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        if (logstream != nullptr)
        {
            GLchar infoLog[512];
            glGetShaderInfoLog(m_d->m_id, 512, NULL, infoLog);
            *logstream << "ERROR::SHADER::" << ShaderTypeHelper<shaderType>::GetName()
                << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        return false;
    }

    return true;
}

template<ShaderType shaderType>
Ptr<Core::Object> Shader<shaderType>::LoadFromFile(std::ifstream& file)
{
    std::string tmp;

    Ptr<Core::Object> result;

    while (std::getline(file, tmp))
    {
        std::istringstream stream(tmp);

        stream >> tmp;
        
        if (tmp == "Path")
        {
            stream >> tmp;
            auto res = new Shader<shaderType>();
            res->Compile(tmp.c_str(), nullptr, nullptr);
            result = res;
        }
    }

    return result;
}

template<ShaderType shaderType>
bool Shader<shaderType>::Compile(const char* fileName, const char* additionalCode, std::ostream* logstream)
{
    using namespace std::tr2::sys;

    assert(m_d != nullptr);

    if (!exists(fileName))
    {
        if (logstream != nullptr)
        {
            *logstream << "ERROR::SHADER::" << ShaderTypeHelper<shaderType>::GetName()
                << std::endl << "file not found" << std::endl;
        }

        return false;
    }

    std::ifstream is(fileName, std::ifstream::binary);
    if (is)
    {
        // get length of file :
        is.seekg(0, is.end);
        size_t length = static_cast<size_t>(is.tellg());
        is.seekg(0, is.beg);

        m_d->m_code.resize(length + 1);
        if (!is.read(&m_d->m_code[0], length) && logstream != nullptr)
        {
            *logstream << "WARNING::SHADER::"
                << ShaderTypeHelper<shaderType>::GetName()
                << std::endl << "only " << is.gcount()
                << " could be read" << std::endl;
        }

        is.close();
    }

    //Compile vertex shader
    if (additionalCode == nullptr)
    {
        const GLchar* shaderCodePtr = m_d->m_code.data();
        glShaderSource(m_d->m_id, 1, &shaderCodePtr, NULL);
    }
    else
    {
        const char * codePointers[2]
        {
            additionalCode,
            m_d->m_code.data()
        };

        glShaderSource(m_d->m_id, 2, codePointers, NULL);
    }

    glCompileShader(m_d->m_id);
    GLint success;
    glGetShaderiv(m_d->m_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        if (logstream != nullptr)
        {
            GLchar infoLog[512];
            glGetShaderInfoLog(m_d->m_id, 512, NULL, infoLog);
            *logstream << "ERROR::SHADER::" << ShaderTypeHelper<shaderType>::GetName()
                << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        return false;
    }

    return true;
}

template<ShaderType shaderType>
int Shader<shaderType>::GetId() const
{
    assert(m_d != nullptr);
    return m_d->m_id;
}

} }