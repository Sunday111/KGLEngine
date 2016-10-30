#ifndef KGL_CORE_FWDDECL_H_INCLUDED
#define KGL_CORE_FWDDECL_H_INCLUDED

#include <memory>

#define KGL_CORE_FWDDECLOBJ(T) \
    class T;\
    typedef std::shared_ptr<T> T##SharedPtr;\
    typedef std::shared_ptr<const T> T##ConstSharedPtr;\
    typedef std::unique_ptr<T> T##UniquePtr;\
    typedef std::unique_ptr<const T> T##ConstUniquePtr;

namespace KGL { namespace Core {

KGL_CORE_FWDDECLOBJ(Object);
KGL_CORE_FWDDECLOBJ(IApplication);

} }

#endif /* KGL_CORE_FWDDECL_H_INCLUDED */