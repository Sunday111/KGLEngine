#ifndef KGL_BASE_MACRO_H_INCLUDED
#define KGL_BASE_MACRO_H_INCLUDED

#include <cassert>

#ifndef SAFE_DELETE
	#define SAFE_DELETE(ptr) { if(ptr != nullptr) delete ptr; }
#else
pragma error "Already defined SAFE_DELETE"
#endif

#ifndef SAFE_ARRAY_DELETE
#define SAFE_ARRAY_DELETE(ptr) { if(ptr != nullptr) delete [] ptr; }
#else
pragma error "Already defined SAFE_ARRAY_DELETE"
#endif

#ifndef assertexpr
#ifdef _DEBUG
#define assertexpr(expr) assert(expr)
#else
#define assertexpr(expr) expr
#endif
#else
pragma error "Already defined assertexpr"
#endif

#ifndef InstanceCreatorInstantiation
// default version
#define InstanceCreatorInstantiation(Creator, Interface, Implementation, pointerType, ...)\
	template<>\
	typename Creator<Interface, pointerType>::Pointer \
	Creator<Interface, pointerType>::CreateInstance() \
	{ \
		return KGL::PointerTypeHelper<Implementation, pointerType>::Create(__VA_ARGS__); \
	} \
	template class Creator<Interface, pointerType>
#else
pragma error "Already defined InstanceCreatorInstantiation"
#endif

#ifndef DECLARE_CLASS_RTTI
#define DECLARE_CLASS_RTTI(type, ...) \
        public: \
            int GetTypeId() const override; \
            static const int typeId; \
            bool IsTypeOf(int typeId) const override;
#else
pragma error "Already defined DECLARE_CLASS_RTTI"
#endif

/* Use this macro in global namespace only */
#ifndef DEFINE_CLASS_RTTI
#define DEFINE_CLASS_RTTI(type, ...) \
            const int type::typeId = []() \
            { \
                const int thisTypeId = KGL::Core::TypeRegistry::GetInstance()->GetNextTypeId(); \
                auto pTr = KGL::Core::TypeRegistry::GetInstance(); \
                if(!pTr->TypeRegistered(thisTypeId)) \
                { \
                    std::vector<int> parents; \
                    auto fn = KGL::Core::Rtti::GetLoadFromFileMethod<type>(KGL::Core::Rtti::_special()); \
                    KGL::Core::Rtti::RttiHelper<type, __VA_ARGS__>::CreateIdArray(parents); \
                    pTr->RegisterType(thisTypeId, #type, fn, std::move(parents)); \
                } \
                return thisTypeId; \
            }(); \
            \
            bool type::IsTypeOf(int id) const \
            { \
                return KGL::Core::TypeRegistry::GetInstance()->IsTypeOf(type::typeId, id); \
            } \
            int type::GetTypeId() const { return type::typeId; }
#else
    pragma error "Already defined DEFINE_CLASS_RTTI"
#endif

#endif /* KGL_BASE_MACRO_H_INCLUDED */