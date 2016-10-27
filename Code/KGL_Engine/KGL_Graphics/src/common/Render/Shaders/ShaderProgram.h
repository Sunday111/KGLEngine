#ifndef KGL_GRAPHICS_SHADER_PROGRAM_H_INCLUDED
#define KGL_GRAPHICS_SHADER_PROGRAM_H_INCLUDED

#include <memory>
#include <vector>
#include <KGL_Base/PointersVector.h>
#include <KGL_Core/RTTI.h>
#include <KGL_Graphics/Render/Shaders/IShaderProgram.h>
#include "Object.h"

namespace KGL { namespace Graphics {

class ShaderProgram :
	public virtual IShaderProgram,
    public virtual Graphics::Object
{
public:
	ShaderProgram();
	~ShaderProgram();

	int GetId() override { return m_id; }
    bool AddShader(std::unique_ptr<IShader> shader, bool replace) override;
    bool AddShader(std::shared_ptr<IShader> shader, bool replace) override;
	bool Link(std::ostream* logstream) override;
	bool Use() override;
	int GetVariableLocation(const char* name) override;

    DECLARE_SUPPORT_RTTI(ShaderProgram, Graphics::Object)

private:

	int m_id;
	bool m_linked;
    PointersArray<IShader> m_shaders;
};

} }


#endif /* KGL_GRAPHICS_SHADER_PROGRAM_H_INCLUDED */