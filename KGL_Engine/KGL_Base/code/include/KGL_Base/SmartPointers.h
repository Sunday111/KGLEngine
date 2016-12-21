#ifndef KGL_BASE_SHARED_POINTER_H_INCLUDED
#define KGL_BASE_SHARED_POINTER_H_INCLUDED

#include <memory>

namespace KGL {

enum class PointerType
{
    Shared,
    Unique
};

template<class T, PointerType pt>
class PointerTypeHelper;

template<class T>
class PointerTypeHelper<T, PointerType::Shared>
{
public:
    using Pointer = std::shared_ptr<T>;

    template<typename... U>
    static Pointer Create(U&&... args)
    {
        return std::make_shared<T>(std::forward<U>(args)...);
    }
};

template<class T>
class PointerTypeHelper<T, PointerType::Unique>
{
public:
    using Pointer = std::unique_ptr<T>;

    template<typename... U>
    static Pointer Create(U&&... args)
    {
        return std::make_unique<T>(std::forward<U>(args)...);
    }
};

}

#endif /* KGL_BASE_SHARED_POINTER_H_INCLUDED */