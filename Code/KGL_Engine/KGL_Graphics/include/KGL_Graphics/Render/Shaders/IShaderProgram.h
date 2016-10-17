#ifndef KGL_GRAPHICS_ISHADER_PROGRAM_H_INCLUDED
#define KGL_GRAPHICS_ISHADER_PROGRAM_H_INCLUDED

#include <KGL_Core/IObject.h>
#include <memory>
#include <ostream>

namespace KGL { namespace Graphics {

class IShader;

class IShaderProgram : public Core::IObject
{
public:
	virtual int GetId() = 0;
	virtual bool AddShader(std::unique_ptr<IShader> shader, bool replace) = 0;
	virtual bool Link(std::ostream* logstream) = 0;
	virtual bool Use() = 0;
	virtual int GetVariableLocation(const char* name) = 0;
};

} }

#endif /* KGL_GRAPHICS_ISHADER_PROGRAM_H_INCLUDED */