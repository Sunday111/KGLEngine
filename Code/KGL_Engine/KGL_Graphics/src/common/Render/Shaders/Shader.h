#ifndef KGL_GRAPHICS_SHADER_H_INCLUDED
#define KGL_GRAPHICS_SHADER_H_INCLUDED

#include <KGL_Graphics/Render/Shaders/IShader.h>
#include "Object.h"

namespace KGL { namespace Graphics {

template<ShaderType shaderType>
class Shader :
	public virtual IShader,
	public virtual Object
{
public:
	Shader();
	~Shader();

	int GetId() override { return m_id; }

	bool Compile(const char* fileName, const char* additionalCode, std::ostream* logstream) override;
	bool RecompileShaderWithCode(const char* code, std::ostream* logstream) override;
	ShaderType GetType() override { return shaderType; }

private:
	const int m_id;
	std::string m_code;
};

} }

#endif /* KGL_GRAPHICS_SHADER_H_INCLUDED */