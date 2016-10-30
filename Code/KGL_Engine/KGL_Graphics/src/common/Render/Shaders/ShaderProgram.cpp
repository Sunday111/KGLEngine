#include <KGL_Core/RTTI.h>
#include <KGL_Graphics/Render/Shaders/Shader.h>
#include <KGL_Graphics/Render/Shaders/ShaderProgram.h>

#include <cassert>

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

namespace KGL {
namespace Graphics {

class ShaderProgram::Impl
{
public:
	Impl() :
		m_id(glCreateProgram()),
		m_linked(false)
	{}

	~Impl()
	{
		glDeleteProgram(m_id);
	}

	template<ShaderType st>
	Ptr<Shader<st>>& GetShader();

	template<>
	Ptr<Shader<ShaderType::Vertex>>& GetShader()
	{
		return m_vertexShader;
	}

	template<>
	Ptr<Shader<ShaderType::Fragment>>& GetShader()
	{
		return m_fragmentShader;
	}

	template<ShaderType st>
	bool Attach()
	{
		auto& sh = GetShader<st>();
		if (sh == nullptr)
		{
			return false;
		}

		glAttachShader(m_id, sh->GetId());
		return true;
	}

	int m_id;
	bool m_linked;
	Ptr<Shader<ShaderType::Vertex>> m_vertexShader;
	Ptr<Shader<ShaderType::Fragment>> m_fragmentShader;
};

DEFINE_SUPPORT_RTTI(ShaderProgram, Object)

ShaderProgram::ShaderProgram() :
	m_d(new Impl)
{}

ShaderProgram::~ShaderProgram()
{
	assert(m_d != nullptr);
	delete m_d;
}

int ShaderProgram::GetId() const
{
	assert(m_d != nullptr);
	return m_d->m_id;
}

template<ShaderType st>
bool ShaderProgram::AddShader(Ptr<Shader<st>> shader, bool replace)
{
	assert(m_d != nullptr);

	auto& sh = m_d->GetShader<st>();

	if (sh == nullptr || replace)
	{
		sh = shader;
		return true;
	}

	return false;
}

bool ShaderProgram::Link(std::ostream* logstream)
{
	assert(m_d != nullptr);

	m_d->m_linked = false;

	static_assert((int)(ShaderType::__last) == 2,
		"Extend here for new shader types");

	m_d->Attach<ShaderType::Vertex>();
	m_d->Attach<ShaderType::Fragment>();

	glLinkProgram(m_d->m_id);

	GLint success;
	glGetProgramiv(m_d->m_id, GL_LINK_STATUS, &success);

	m_d->m_linked = success == 1;

	if (!m_d->m_linked) {
		if (logstream != nullptr)
		{
			GLchar infoLog[512];
			glGetProgramInfoLog(m_d->m_id, 512, NULL, infoLog);
			*logstream << "ERROR::SHADER_PROGRAM::" << m_d->m_id
				<< "::LINK_FAILED\n" << infoLog << std::endl;
		}
	}

	return m_d->m_linked;
}

bool ShaderProgram::Use()
{
	if (m_d->m_linked)
	{
		glUseProgram(m_d->m_id);
	}

	return m_d->m_linked;
}

int ShaderProgram::GetVariableLocation(const char* name)
{
	return glGetUniformLocation(m_d->m_id, name);
}

#define INSTANTIATE_ADD_SHADER(shaderType)\
template bool ShaderProgram::AddShader<shaderType>(Ptr<Shader<shaderType>> shader, bool replace);

INSTANTIATE_ADD_SHADER(ShaderType::Vertex);
INSTANTIATE_ADD_SHADER(ShaderType::Fragment);

} }