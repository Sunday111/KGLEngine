#ifndef KGL_GRAPHICS_SHADER_H_INCLUDED
#define KGL_GRAPHICS_SHADER_H_INCLUDED

#include <fstream>
#include <ostream>
#include <KGL_Base/Ptr.h>
#include <KGL_Core/Object.h>
#include <KGL_Graphics/Object.h>
#include <KGL_Graphics/Render/Shaders/ShaderType.h>

namespace KGL { namespace Core {

class Resource;

} }

namespace KGL { namespace Graphics {


template<ShaderType shaderType>
class KGL_GRAPHICS_API Shader : public Object
{
	DECLARE_CLASS_RTTI(Shader<shaderType>, Object)

public:
	Shader();
	~Shader();

	int GetId() const;
	bool Compile(const char* fileName, const char* additionalCode, std::ostream* logstream);
	bool RecompileShaderWithCode(const char* code, std::ostream* logstream);
	static Ptr<Core::Object> LoadFromFile(std::ifstream& stream);

private:
	class Impl;
	Impl* m_d;
};

} }

#endif