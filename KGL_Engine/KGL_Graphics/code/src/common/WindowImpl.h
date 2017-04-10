#ifndef KGL_GRAPHICS_WINDOW_IMPL_H_INCLUDED
#define KGL_GRAPHICS_WINDOW_IMPL_H_INCLUDED

#include <KGL_Base/Ptr.h>

#include <assert.h>
#include <memory>
#include <set>

struct GLFWwindow;
namespace KGL { namespace Core {

class Application;

} }

namespace KGL { namespace Graphics {

class RenderContext;
class ShaderProgram;
class WindowListener;
class WindowManagerImpl;

class WindowImpl
{
public:
    explicit WindowImpl(WindowManagerImpl* mgr, Core::Application* app, Ptr<RenderContext> context);
    ~WindowImpl();

    int GetId() const { return m_id; }
    bool AddListener(WindowListener* listener);
    bool RemoveListener(WindowListener* listener);
    bool ShouldClose() const;
    void Update() const;
    const Ptr<RenderContext>& GetContext() const { return m_context; }

private:
    int m_id;
    WindowManagerImpl* m_mgr;
    std::set<WindowListener*> m_listeners;
    GLFWwindow* m_window;
    Ptr<RenderContext> m_context;

    std::unique_ptr<ShaderProgram> testShader;
    unsigned int VBO, VAO, EBO;
};

} }

#endif