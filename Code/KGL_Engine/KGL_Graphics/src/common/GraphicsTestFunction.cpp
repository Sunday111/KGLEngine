#include <KGL_Graphics/GraphicsTestFunction.h>
#include <cassert>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

namespace KGL { namespace Graphics {

void GraphicsTestFunction()
{
    assert(!"Graphics dll call");
}

}}