#ifndef KGL_CORE_PTR_H_INCUDED
#define KGL_CORE_PTR_H_INCUDED

#include <cassert>
#include <type_traits>

namespace KGL {

template<class T>
class Ptr
{
public:
	Ptr() : m_p(nullptr) {}

	Ptr(std::nullptr_t) : m_p(nullptr) {}

	Ptr(T* p) :
		m_p(p)
	{
		AddReference();
	}

	explicit Ptr(Ptr&& ptr) :
		m_p(ptr.m_p)
	{
		ptr.m_p = nullptr;
	}

	explicit Ptr(const Ptr& ptr) :
		m_p(ptr.m_p)
	{
		AddReference();
	}

	template<typename U>
	Ptr(const Ptr<U>& ip,
			typename std::enable_if<std::is_convertible<U*, T*>::value, int>::type = 0) :
		m_p(ip.m_p)
	{
		AddReference();
	}

	template<typename U>
	Ptr(Ptr<U>&& ip,
		typename std::enable_if<std::is_convertible<U*, T*>::value, int>::type = 0) :
		m_p(ip.m_p)
	{
		ip.m_p = nullptr;
	}

	~Ptr()
	{
		RemoveReference();
	}

	void reset()
	{
		RemoveReference(m_p);
		m_p = nullptr;
	}

	Ptr& swap(Ptr& p)
	{
		T* tmp = m_p;

		m_p = p.m_p;
		p.m_p = tmp;

		return *this;
	}

	template<typename U>
	Ptr<U> StaticCast() const
	{
		typename Ptr<U>::StaticCastTag UStaticCastTag;
		return Ptr<U>(*this, UStaticCastTag);
	}

	Ptr& operator=(const Ptr& ptr)
	{
		if (this != &ptr)
		{
			RemoveReference();

			m_p = ptr.m_p;

			AddReference();
		}

		return *this;
	}

	Ptr& operator=(Ptr&& ptr)
	{
		if (this != &ptr)
		{
			if (m_p != nullptr)
			{
				RemoveReference(m_p);
			}

			m_p = ptr.m_p;
			ptr.m_p = nullptr;
		}

		return *this;
	}

	template<typename U>
	Ptr& operator=(const Ptr<U>& ptr)
	{
		if (this != &ptr)
		{
			RemoveReference(m_p);

			m_p = ptr.m_p;

			AddReference(m_p);
		}

		return *this;
	}

	template<typename U>
	Ptr& operator=(Ptr<U>&& ptr)
	{
		if (this != &ptr)
		{
			RemoveReference(m_p);

			m_p = ptr.m_p;
			ptr.m_p = nullptr;
		}

		return *this;
	}

    bool operator==(std::nullptr_t) const { return m_p == nullptr; }
    bool operator!=(std::nullptr_t) const { return m_p != nullptr; }

	template<typename U>
	bool operator==(const Ptr<U>& p) const { return m_p == p.m_p; }

	template<typename U>
	bool operator!=(const Ptr<U>& p) { return m_p != p.m_p; }

	template<typename U>
	bool operator<(const Ptr<U>& p) const { return m_p < p.m_p; }

	T* operator->() const { assert(m_p != nullptr); return m_p; }
	T& operator*() const { assert(m_p != nullptr); return *m_p; }

protected:
	inline void AddReference()
	{
		if (m_p != nullptr)
		{
			KGL::Core::AddReference(m_p);
		}
	}

	inline void RemoveReference()
	{
		if (m_p != nullptr)
		{
			KGL::Core::RemoveReference(m_p);
		}
	}

private:
	template<typename U>
	friend class Ptr;

	struct StaticCastTag {};

	template<typename U>
	Ptr(const Ptr<U>& ip, StaticCastTag) :
		m_p(static_cast<T*>(ip.m_p))
	{
		if (m_p != nullptr)
		{
			AddReference(m_p);
		}
	}

	T* m_p;
};

}

namespace std {

template<typename U, typename T>
KGL::Ptr<U> static_pointer_cast(const KGL::Ptr<T>& ip)
{
	return ip.template StaticCast<U>();
}

}

#endif