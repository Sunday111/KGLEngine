#include <KGL_Graphics/Render/Shaders/IShader.h>

#include <cassert>

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include "ShaderProgram.h"

namespace KGL { namespace Graphics { namespace
{

template<class T>
bool Add(
	PointersArray<IShader>& m_shaders,
	int& m_id, bool& m_linked,
	T shader, bool replace)
{
	for (int i = 0; i < m_shaders.Size(); ++i)
	{
		auto s = m_shaders[i];

		if (s->GetType() == shader->GetType())
		{
			if (replace)
			{
				glDetachShader(m_id, s->GetId());
				m_linked = false;
				m_shaders.Erase(i);
			}
			else
			{
				return false;
			}
		}
	}

	return m_shaders.AddUnique(std::forward<T&&>(shader));
}

}

DEFINE_SUPPORT_RTTI(ShaderProgram, Graphics::Object)

ShaderProgram::ShaderProgram() :
	m_id(glCreateProgram()),
	m_linked(false)
{}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_id);
}

bool ShaderProgram::AddShader(std::unique_ptr<IShader> shader, bool replace)
{
	return Add(m_shaders, m_id, m_linked, std::move(shader), replace);
}

bool ShaderProgram::AddShader(std::shared_ptr<IShader> shader, bool replace)
{
	return Add(m_shaders, m_id, m_linked, shader, replace);
}

bool ShaderProgram::Link(std::ostream* logstream)
{
	m_linked = false;

	for (auto& s : m_shaders)
	{
		glAttachShader(m_id, s->GetId());
	}

	glLinkProgram(m_id);

	GLint success;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);

	m_linked = success == 1;

	if (!m_linked) {
		if (logstream != nullptr)
		{
			GLchar infoLog[512];
			glGetProgramInfoLog(m_id, 512, NULL, infoLog);
			*logstream << "ERROR::SHADER_PROGRAM::" << m_id
				<< "::LINK_FAILED\n" << infoLog << std::endl;
		}
	}

	return m_linked;
}

bool ShaderProgram::Use()
{
	if (m_linked)
	{
		glUseProgram(m_id);
	}

	return m_linked;
}

int ShaderProgram::GetVariableLocation(const char* name)
{
	return glGetUniformLocation(m_id, name);
}

} }