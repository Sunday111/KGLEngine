#ifndef KGL_GRAPHICS_SHADER_PROGRAM_H_INCLUDED
#define KGL_GRAPHICS_SHADER_PROGRAM_H_INCLUDED

#include <KGL_Base/Ptr.h>
#include <KGL_Graphics/Object.h>
#include <KGL_Graphics/Render/Shaders/ShaderType.h>
#include <memory>
#include <ostream>

namespace KGL { namespace Graphics {

template<ShaderType>
class Shader;

class ShaderProgram : public Object
{
	DECLARE_CLASS_RTTI(ShaderProgram, Object)

public:
	ShaderProgram();
	~ShaderProgram();

	int GetId() const;

	template<ShaderType st>
    bool AddShader(Ptr<Shader<st>> shader, bool replace);

	bool Link(std::ostream* logstream);
	bool Use();
	int GetVariableLocation(const char* name);

private:
	class Impl;
	Impl* m_d;
};

} }

#endif