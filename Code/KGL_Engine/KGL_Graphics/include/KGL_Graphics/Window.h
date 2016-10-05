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
    /* Id of exisiting window created by Window manager
     */
    Window();
    explicit Window(int id, WindowManager* mgr);

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

    bool ShouldClose() const;

    int GetId() const;

private:
    int m_id;
    WindowManager* m_mgr;
};

} }

#endif /*KGL_GRAPHICS_WINDOW_H_INCLUDED*/