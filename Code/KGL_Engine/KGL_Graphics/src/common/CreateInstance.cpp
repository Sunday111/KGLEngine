#include <cassert>
#include "KGL_Base/Marco.h"
#include "KGL_Graphics/CreateInstance.h"
#include "Render/Shaders/Shader.h"
#include "Render/Shaders/ShaderProgram.h"

InstanceCreatorInstantiationBothPointers(KGL::Graphics::InstanceCreator, KGL::Graphics::IShaderProgram, KGL::Graphics::ShaderProgram);

namespace KGL { namespace Graphics {

namespace
{

template<PointerType pt>
typename InstanceCreator<IShader, pt, ShaderType>::Pointer
CreateShaderByType(ShaderType st)
{
	switch (st)
	{
	case ShaderType::Vertex:
		return KGL::PointerTypeHelper<Shader<ShaderType::Vertex>, pt>::Create();
		break;
	case ShaderType::Fragment:
		return KGL::PointerTypeHelper<Shader<ShaderType::Fragment>, pt>::Create();
		break;
	default:
		assert(!"Not implemented here");
		return nullptr;
	}
}

}

InstanceCreatorInstantiationExBothPointers(
	KGL::Graphics::InstanceCreator,
	KGL::Graphics::IShader,
	KGL::Graphics::Shader<ShaderType::Vertex>,
	CreateShaderByType<PointerType::Unique>,
	ShaderType::Vertex);

InstanceCreatorInstantiationExBothPointers(
	KGL::Graphics::InstanceCreator,
	KGL::Graphics::IShader,
	KGL::Graphics::Shader<ShaderType::Fragment>,
	CreateShaderByType<PointerType::Unique>,
	ShaderType::Fragment);

} }