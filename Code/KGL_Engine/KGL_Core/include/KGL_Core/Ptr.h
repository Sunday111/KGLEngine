#ifndef KGL_CORE_PTR_H_INCUDED
#define KGL_CORE_PTR_H_INCUDED

#include <cassert>
#include <KGL_Core/IObject.h>

namespace KGL { namespace Core {

template<class T>
class Ptr
{
public:
	Ptr(T* p) :
		m_p(p)
	{
		assert(p != nullptr);
		AddReference(p);
	}

	explicit Ptr(Ptr&& ptr) :
		m_p(ptr.m_p)
	{
		ptr.m_p = nullptr;
	}

	explicit Ptr(const Ptr& ptr) :
		m_p(ptr.m_p)
	{
		AddReference(p);
	}

	~Ptr()
	{
		RemoveReference(m_p);
	}

	Ptr& operator=(const Ptr& ptr)
	{
		if (this != &ptr)
		{
			if (m_p != nullptr)
			{
				RemoveReference(m_p);
			}

			m_p = ptr.m_p;
			AddReference(m_p);
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

	friend bool operator==(const Ptr& l, const Ptr& r)
	{
		return l.m_p == r.m_p;
	}
	friend bool operator!=(const Ptr& l, const Ptr& r)
	{
		return l.m_p != r.m_p;
	}

	operator T*()
	{
		return m_p;
	}
	operator const T*() const
	{
		return m_p;
	}

	T* operator->()
	{
		return m_p;
	}
	const T* operator->() const
	{
		return m_p;
	}
private:
	T* m_p;
};

} }

#endif /* KGL_CORE_PTR_H_INCUDED */