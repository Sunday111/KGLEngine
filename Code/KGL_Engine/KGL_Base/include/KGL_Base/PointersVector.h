#ifndef KGL_BASE_POINTERS_ARRAY_H_INCLUDED
#define KGL_BASE_POINTERS_ARRAY_H_INCLUDED

#include <KGL_Base/SmartPointers.h>
#include <vector>

namespace KGL
{

template<class T>
class PointersArray
{
public:


    using Shared = typename PointerTypeHelper<T, PointerType::Shared>::Pointer;
    using Unique = typename PointerTypeHelper<T, PointerType::Unique>::Pointer;

	class Element
	{
	public:
		explicit Element(Unique&& p) :
			m_unique(std::move(p))
		{}
		explicit Element(const Shared& p) :
			m_shared(p)
		{}
		explicit Element(Element&& rhs) :
			m_unique(std::move(rhs.m_unique)),
			m_shared(std::move(rhs.m_shared))
		{}
		Element(const Element&) = delete;

		T* GetUnique()
		{
			return m_unique.get();
		}

		const T* GetUnique() const
		{
			return m_unique.get();
		}

		T* GetShared()
		{
			return m_shared;
		}

		const T* GetShared() const
		{
			return m_shared;
		}

		void Swap(Element& e)
		{
			std::swap(m_unique, e.m_unique);
			std::swap(m_shared, e.m_shared);
		}

		friend bool operator== (const Element& lhs, const Unique& rhs)
		{
			return static_cast<const T*>(lhs) == rhs.get();
		}
		friend bool operator== (const Element& lhs, const Shared& rhs)
		{
			return static_cast<const T*>(lhs) == rhs.get();
		}
		friend bool operator== (const Element& lhs, const Element& rhs)
		{
			return
				static_cast<const T*>(lhs) ==
				static_cast<const T*>(rhs);
		}
		friend bool operator != (const Element& lhs, const Element& rhs)
		{
			return !operator==(lhs, rhs);
		}
		Element& operator=(Element&& e)
		{
			if (this != &e)
			{
				m_shared = e.m_shared;
				m_unique = std::move(e.m_unique);
			}

			return *this;
		}
		Element& operator=(const Element& e) = delete;
		T* operator->()
		{
			return Get();
		}
		const T* operator->() const
		{
			return Get();
		}

		operator T*()
		{
			return Get();
		}

		operator const T*() const
		{
			return Get();
		}
		
		T* Get()
		{
			return const_cast<T*>(const_cast<const Element*>(this)->Get());
		}

		const T* Get() const
		{
			assert(m_unique != nullptr ^ m_shared != nullptr);

			if (m_unique != nullptr)
			{
				return m_unique.get();
			}

			return m_shared.get();
		}

	private:
		Shared m_shared;
		Unique m_unique;
	};

    using Collection = std::vector<Element>;
	using iterator = typename Collection::iterator;
	using const_iterator = typename Collection::const_iterator;

	template<class T>
	void Add(T p)
	{
		m_pointers.push_back(Element(std::forward<T&&>(p)));
	}

	template<class T>
	bool AddUnique(T p)
	{
		if (std::find(m_pointers.begin(), m_pointers.end(), p)
			!= m_pointers.end())
		{
			return false;
		}

		Add(std::forward<T&&>(p));
		return true;
	}

    iterator begin()
    {
        return m_pointers.begin();
    }

    iterator end()
    {
        return m_pointers.end();
    }

	void Erase(size_t index)
	{
		m_pointers.erase(m_pointers.begin() + index);
	}

	size_t Size() const
	{
		return m_pointers.size();
	}

	T* operator[](size_t index)
	{
		return m_pointers[index].Get();
	}

	const T* operator[](size_t index) const
	{
		return m_pointers[index].Get();
	}

private:

    std::vector<Element> m_pointers;
};

}

namespace std
{

template<class T>
void swap(typename KGL::PointersArray<T>::Element& lhs,
	typename KGL::PointersArray<T>::Element& rhs)
{
	lhs.Swap(rhs);
}

}

#endif /* KGL_BASE_POINTERS_ARRAY_H_INCLUDED */