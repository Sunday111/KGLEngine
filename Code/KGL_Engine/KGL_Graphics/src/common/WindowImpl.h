#ifndef KGL_GRAPHICS_WINDOW_IMPL_H_INCLUDED
#define KGL_GRAPHICS_WINDOW_IMPL_H_INCLUDED

#include <assert.h>
#include <memory>
#include <set>

struct GLFWwindow;
namespace KGL { namespace Core {

class Application;

} }

namespace KGL { namespace Graphics {

class ShaderProgram;
class WindowListener;
class WindowManagerImpl;

class WindowImpl
{
public:
    explicit WindowImpl(WindowManagerImpl* mgr, Core::Application* app);
    ~WindowImpl();

    int GetId() const { return m_id; }
    bool AddListener(WindowListener* listener);
    bool RemoveListener(WindowListener* listener);
    bool ShouldClose() const;
    void Update() const;

private:
    int m_id;
    GLFWwindow* m_wnd;
    WindowManagerImpl* m_mgr;
    std::set<WindowListener*> m_listeners;

    std::unique_ptr<ShaderProgram> testShader;
    unsigned int VBO, VAO, EBO;
};

} }

#endif