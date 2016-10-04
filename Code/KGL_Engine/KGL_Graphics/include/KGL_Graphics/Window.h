#ifndef KGL_GRAPHICS_WINDOW_H_INCLUDED
#define KGL_GRAPHICS_WINDOW_H_INCLUDED

#include "KGL_Graphics/Common.h"

namespace KGL { namespace Graphics {

class WindowImpl;
class WindowManager;

class KGL_GRAPHICS_API WindowListener
{
public:
    virtual ~WindowListener() = default;
};

class KGL_GRAPHICS_API Window
{
public:
    explicit Window(WindowManager*);
    explicit Window(const Window&) = delete;
    explicit Window(Window&& uref);
    ~Window();

    /* Add window listener object.
     * Returns false if such listener is already added
     * or when object is empty (m_d == nullptr)
     */
    bool AddListener(WindowListener* listener);

    /* Remove windown listener object.
     * Returns false if specified objects is not added.
     * or when object is empty (m_d == nullptr)
     */
    bool RemoveListener(WindowListener* listener);

private:
    WindowImpl* m_d;
};

} }

#endif /*KGL_GRAPHICS_WINDOW_H_INCLUDED*/