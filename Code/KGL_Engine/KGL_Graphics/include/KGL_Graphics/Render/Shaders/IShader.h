#ifndef KGL_GRAPHICS_ISHADER_H_INCLUDED
#define KGL_GRAPHICS_ISHADER_H_INCLUDED

#include <ostream>
#include <KGL_Core/Object.h>
#include <KGL_Graphics/Render/Shaders/ShaderType.h>

namespace KGL { namespace Graphics {

class KGL_GRAPHICS_API IShader : public Core::Object
{
public:
	virtual int GetId() = 0;
	virtual bool Compile(const char* fileName, const char* additionalCode, std::ostream* logstream) = 0;
	virtual bool RecompileShaderWithCode(const char* code, std::ostream* logstream) = 0;
	virtual ShaderType GetType() = 0;
};

} }

#endif /* KGL_GRAPHICS_ISHADER_H_INCLUDED */