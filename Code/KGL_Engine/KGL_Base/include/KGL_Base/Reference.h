#ifndef KGL_BASE_REFERENCE_H_INCLUDED
#define KGL_BASE_REFERENCE_H_INCLUDED

#include <type_traits>

namespace KGL
{

template<typename T>
class Reference
{
public:
    typedef T* pointer;
    typedef T& reference;

    struct NoAddRef {};

    static const Reference kNull;

    Reference() : m_p(nullptr) {}

    Reference(std::nullptr_t) : m_p(nullptr) {}

    explicit Reference(pointer p) :
        m_p(p)
    {
        if (m_p != nullptr)
        {
            ReferenceAddRef(m_p);
        }
    }

    explicit Reference(pointer p, NoAddRef) : m_p(p) {}

    Reference(const Reference& ip) :
        m_p(ip.m_p)
    {
        if (m_p != nullptr)
        {
            ReferenceAddRef(m_p);
        }
    }

    Reference(Reference&& ip) :
        m_p(ip.m_p)
    {
        ip.m_p = nullptr;
    }

    template<typename U>
    Reference(const Reference<U>& ip,
        typename std::enable_if<std::is_convertible<U*, T*>::value, int>::type = 0) :
        m_p(ip.m_p)
    {
        if (m_p != nullptr)
        {
            ReferenceAddRef(m_p);
        }
    }

    template<typename U>
    Reference(Reference<U>&& ip,
        typename std::enable_if<std::is_convertible<U*, T*>::value, int>::type = 0) :
        m_p(ip.m_p)
    {
        ip.m_p = nullptr;
    }

    ~Reference()
    {
        if (m_p != nullptr)
        {
            ReferenceReleaseRef(m_p);
			m_p = nullptr;
        }
    }

    void reset()
    {
        if (m_p != nullptr)
        {
            pointer p = m_p;

            m_p = nullptr;

            ReferenceReleaseRef(p);
        }
    }

    pointer release()
    {
        pointer p = m_p;

        m_p = nullptr;

        return p;
    }

    pointer get() const { return m_p; }

    pointer operator->() const { assert(m_p != nullptr); return m_p; }
    reference operator*() const { assert(m_p != nullptr); return *m_p; }

    bool unique() const
    {
        return m_p != nullptr ? ReferenceCountRef(m_p) == 1 : false;
    }

    Reference& swap(Reference& ip)
    {
        pointer p = m_p;

        m_p = ip.m_p;
        ip.m_p = p;

        return *this;
    }

    Reference& operator=(std::nullptr_t)
    {
        reset();

        return *this;
    }

    Reference& operator=(pointer p)
    {
        pointer tp = m_p;

        m_p = p;

        if (m_p != nullptr)
        {
            ReferenceAddRef(m_p);
        }

        if (tp != nullptr)
        {
            ReferenceReleaseRef(tp);
        }

        return *this;
    }

    Reference& operator=(const Reference& ip)
    {
        pointer p = m_p;

        m_p = ip.m_p;

        if (m_p != nullptr)
        {
            ReferenceAddRef(m_p);
        }

        if (p != nullptr)
        {
            ReferenceReleaseRef(p);
        }

        return *this;
    }

    Reference& operator=(Reference&& ip)
    {
        if (this != &ip)
        {
            pointer p = m_p;

            m_p = ip.m_p;

            ip.m_p = nullptr;

            if (p != nullptr)
            {
                ReferenceReleaseRef(p);
            }
        }

        return *this;
    }

    template<typename U>
    Reference& operator=(const Reference<U>& ip)
    {
        pointer p = m_p;

        m_p = ip.m_p;

        if (m_p != nullptr)
        {
            ReferenceAddRef(m_p);
        }

        if (p != nullptr)
        {
            ReferenceReleaseRef(p);
        }

        return *this;
    }

    template<typename U>
    Reference& operator=(Reference<U>&& ip)
    {
        pointer p = m_p;

        m_p = ip.m_p;
        ip.m_p = nullptr;

        if (p != nullptr)
        {
            ReferenceReleaseRef(p);
        }

        return *this;
    }

    bool operator==(std::nullptr_t) const { return m_p == nullptr; }
    bool operator!=(std::nullptr_t) const { return m_p != nullptr; }

    template<typename U>
    bool operator==(const Reference<U>& p) const { return m_p == p.m_p; }

    template<typename U>
    bool operator!=(const Reference<U>& p) const { return m_p != p.m_p; }

    template<typename U>
    bool operator<(const Reference<U>& p) const { return m_p < p.m_p; }

    template<typename U>
    Reference<U> StaticCast() const
    {
        typename Reference<U>::StaticCastTag UStaticCastTag;

        return Reference<U>(*this, UStaticCastTag);
    }

private:
    // For casting
    template<typename U>
    friend class Reference;

    template<typename U>
    friend struct std::hash;

    struct StaticCastTag { };

    template<typename U>
    Reference(const Reference<U>& ip, StaticCastTag) :
        m_p(static_cast<pointer>(ip.m_p))
    {
        if (m_p != nullptr)
        {
            ReferenceAddRef(m_p);
        }
    }

    pointer m_p;
};

template<typename T>
const Reference<T> Reference<T>::kNull;

}

namespace std {

template<typename U, typename T>
KGL::Reference<U> static_pointer_cast(const KGL::Reference<T>& ip)
{
    return ip.template StaticCast<U>();
}

}

#endif /* KGL_BASE_REFERENCE_H_INCLUDED */