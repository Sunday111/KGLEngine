#include <KGL_Graphics/Render/Shaders/IShader.h>

#include <cassert>

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include "ShaderProgram.h"

namespace KGL { namespace Graphics {

ShaderProgram::ShaderProgram() :
	m_id(glCreateProgram())
{
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_id);
}

bool ShaderProgram::AddShader(std::unique_ptr<IShader> shader, bool replace)
{
	for (auto& s : m_shaders)
	{
		if (s->GetType() == shader->GetType())
		{
			if (replace)
			{
				std::swap(s, shader);
				return true;
			}

			return false;
		}
	}

	m_shaders.push_back(std::move(shader));
	return true;
}

bool ShaderProgram::Link(std::ostream* logstream)
{
	for (auto& s : m_shaders)
	{
		glAttachShader(m_id, s->GetId());
	}

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

void ShaderProgram::Use()
{
	glUseProgram(m_id);
}

int ShaderProgram::GetVariableLocation(const char* name)
{
	return glGetUniformLocation(m_id, name);
}

} }