#include "Shader.h"
#include <cassert>
#include <fstream>
#include <filesystem>

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

namespace KGL { namespace Graphics {

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

template<ShaderType shaderType>
Shader<shaderType>::Shader() :
	m_id(glCreateShader(ShaderTypeHelper<shaderType>::GL_ShaderType))
{
	GLint success;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);

	if (!success)
	{
		(assert(false));
	}
}

template<ShaderType shaderType>
Shader<shaderType>::~Shader()
{
	glDeleteShader(m_id);
}

template<ShaderType shaderType>
bool Shader<shaderType>::RecompileShaderWithCode(const char* code, std::ostream* logstream)
{
	assert(code != nullptr);

	const char * codePointers[2]
	{
		code,
		m_code.data()
	};

	glShaderSource(m_id, 2, codePointers, NULL);
	glCompileShader(m_id);

	GLint success;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		if (logstream != nullptr)
		{
			GLchar infoLog[512];
			glGetShaderInfoLog(m_id, 512, NULL, infoLog);
			*logstream << "ERROR::SHADER::" << ShaderTypeHelper<shaderType>::GetName()
				<< "::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		return false;
	}

	return true;
}

template<ShaderType shaderType>
bool Shader<shaderType>::Compile(const char* fileName, const char* additionalCode, std::ostream* logstream)
{
	using namespace std::tr2::sys;

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
		size_t length = is.tellg();
		is.seekg(0, is.beg);

		m_code.resize(length + 1);
		if (!is.read(&m_code[0], length) && logstream != nullptr)
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
		const GLchar* shaderCodePtr = m_code.data();
		glShaderSource(m_id, 1, &shaderCodePtr, NULL);
	}
	else
	{
		const char * codePointers[2]
		{
			additionalCode,
			m_code.data()
		};

		glShaderSource(m_id, 2, codePointers, NULL);
	}

	glCompileShader(m_id);
	GLint success;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		if (logstream != nullptr)
		{
			GLchar infoLog[512];
			glGetShaderInfoLog(m_id, 512, NULL, infoLog);
			*logstream << "ERROR::SHADER::" << ShaderTypeHelper<shaderType>::GetName()
				<< "::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		return false;
	}

	return true;
}

template class Shader<ShaderType::Vertex>;
template class Shader<ShaderType::Fragment>;

} }