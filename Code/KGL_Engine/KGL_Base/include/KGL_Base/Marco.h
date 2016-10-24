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

#ifndef InstanceCreatorInstantiationEx
// version with custom construction
#define InstanceCreatorInstantiationEx(Creator, Interface, pointerType, customFunction, argType)\
	template<>\
	typename Creator<Interface, pointerType, argType&&>::Pointer \
	Creator<Interface, pointerType, argType&&>::CreateInstance(argType&& arg) \
	{ \
		return customFunction<pointerType>(std::forward<argType&&>(arg)); \
	} \
	template class Creator<Interface, pointerType, argType&&>
#else
pragma error "Already defined InstanceCreatorInstantiationEx"
#endif

#ifndef InstanceCreatorInstantiationBothPointers
#define InstanceCreatorInstantiationBothPointers(Creator, Interface, Implementation, ...) \
		InstanceCreatorInstantiation(Creator, Interface, Implementation, KGL::PointerType::Unique, __VA_ARGS__); \
		InstanceCreatorInstantiation(Creator, Interface, Implementation, KGL::PointerType::Shared, __VA_ARGS__)
#else
pragma error "Already defined InstanceCreatorInstantiationBothPointers"
#endif

#ifndef InstanceCreatorInstantiationBothPointersEx
#define InstanceCreatorInstantiationBothPointersEx(Creator, Interface, customFunction, argType) \
		InstanceCreatorInstantiationEx(Creator, Interface, KGL::PointerType::Unique, customFunction, argType); \
		InstanceCreatorInstantiationEx(Creator, Interface, KGL::PointerType::Shared, customFunction, argType)
#else
pragma error "Already defined InstanceCreatorInstantiationBothPointersEx"
#endif


#ifndef IMPLEMENT_INTERFACE_DTOR
#define IMPLEMENT_INTERFACE_DTOR(type)\
		type::~type() = default;
#else
pragma error "Already defined IMPLEMENT_INTERFACE_DTOR"
#endif

#ifndef DECLARE_SUPPORT_RTTI
#define DECLARE_SUPPORT_RTTI(type, ...) \
        public: \
            int GetTypeId() const override { return type::TypeId(); } \
            static int TypeId(); \
            bool IsTypeOf(int typeId) const override;
#else
    pragma error "Already defined DECLARE_SUPPORT_RTTI"
#endif

#ifndef DEFINE_SUPPORT_RTTI
    #define DEFINE_SUPPORT_RTTI(type, ...) \
            int type::TypeId() \
            { \
                static const int typeId = KGL::Core::GetTypeRegistry()->GetNextTypeId(); \
                return typeId; \
            } \
            \
            bool type::IsTypeOf(int typeId) const \
            { \
                const int thisTypeId = type::TypeId(); \
                auto pTr = KGL::Core::GetTypeRegistry(); \
                if(!pTr->TypeRegistered(thisTypeId)) \
                { \
                    std::vector<int> parents; \
                    KGL::Core::RttiHelper<type, __VA_ARGS__>::CreateIdArray(parents); \
                    pTr->RegisterType(thisTypeId, std::move(parents)); \
                } \
                return pTr->IsTypeOf(thisTypeId, typeId); \
            }
#else
    pragma error "Already defined DEFINE_SUPPORT_RTTI"
#endif 

#endif /* KGL_BASE_MACRO_H_INCLUDED */