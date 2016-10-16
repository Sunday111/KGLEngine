#ifndef KGL_BASE_MACRO_H_INCLUDED
#define KGL_BASE_MACRO_H_INCLUDED

#define SAFE_DELETE(ptr) { if(ptr != nullptr) delete ptr; }
#define SAFE_ARRAY_DELETE(ptr) { if(ptr != nullptr) delete [] ptr; }

// default version
#define InstanceCreatorInstantiation(Creator, Interface, Implementation, pointerType, ...)\
template<>\
typename Creator<Interface, pointerType>::Pointer \
Creator<Interface, pointerType>::CreateInstance() \
{ \
	return KGL::PointerTypeHelper<Implementation, pointerType>::Create(__VA_ARGS__); \
} \
template class Creator<Interface, pointerType>

// version with custom construction
#define InstanceCreatorInstantiationEx(Creator, Interface, pointerType, customFunction, argType)\
template<>\
typename Creator<Interface, pointerType, argType&&>::Pointer \
Creator<Interface, pointerType, argType&&>::CreateInstance(argType&& arg) \
{ \
	return customFunction<pointerType>(std::forward<argType&&>(arg)); \
} \
template class Creator<Interface, pointerType, argType&&>

#define InstanceCreatorInstantiationBothPointers(Creator, Interface, Implementation, ...) \
	InstanceCreatorInstantiation(Creator, Interface, Implementation, KGL::PointerType::Unique, __VA_ARGS__); \
	InstanceCreatorInstantiation(Creator, Interface, Implementation, KGL::PointerType::Shared, __VA_ARGS__)

#define InstanceCreatorInstantiationBothPointersEx(Creator, Interface, customFunction, argType) \
	InstanceCreatorInstantiationEx(Creator, Interface, KGL::PointerType::Unique, customFunction, argType); \
	InstanceCreatorInstantiationEx(Creator, Interface, KGL::PointerType::Shared, customFunction, argType)


#define IMPLEMENT_INTERFACE_DTOR(type)\
	type::~type() = default;

#endif /* KGL_BASE_MACRO_H_INCLUDED */