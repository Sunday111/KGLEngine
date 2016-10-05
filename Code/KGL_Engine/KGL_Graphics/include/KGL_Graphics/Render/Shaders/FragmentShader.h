#ifndef KGL_GRAPHICS_FRAGMENT_SHADER_H_INCLUDED
#define KGL_GRAPHICS_FRAGMENT_SHADER_H_INCLUDED

#include <KGL_Graphics/Common.h>
#include <memory>
#include <ostream>

namespace KGL { namespace Graphics {

class FragmentShaderImpl;

class KGL_GRAPHICS_API FragmentShader
{
public:
    explicit FragmentShader(const char* fileName,
        const char* additionalCode = nullptr,
        std::ostream* logstream = nullptr);
    FragmentShader(const FragmentShader&) = delete;
    FragmentShader(FragmentShader&& uref);
    ~FragmentShader();

    unsigned int GetId() const;
    bool RecompileShaderWithCode(const char* code,
        std::ostream* logstream = nullptr);

    FragmentShader& operator=(const FragmentShader&) = delete;
    FragmentShader& operator=(FragmentShader&& uref);

private:
    FragmentShaderImpl* m_d;
};

using FragmentShaderPtr = std::shared_ptr<FragmentShader>;

}
}

#endif /* KGL_GRAPHICS_FRAGMENT_SHADER_H_INCLUDED */