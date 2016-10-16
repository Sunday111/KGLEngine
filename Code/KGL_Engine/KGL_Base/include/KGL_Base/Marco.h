#ifndef KGL_BASE_MACRO_H_INCLUDED
#define KGL_BASE_MACRO_H_INCLUDED

#define SAFE_DELETE(ptr) { if(ptr != nullptr) delete ptr; }
#define SAFE_ARRAY_DELETE(ptr) { if(ptr != nullptr) delete [] ptr; }

#define InstanceCreatorInstantiationEx(Creator, Interface, Implementation, pointerType, body, ...)\
template<>\
typename Creator<Interface, pointerType>::Pointer \
Creator<Interface, pointerType>::CreateInstance() \
{ \
	return body(__VA_ARGS__); \
} \
template class Creator<Interface, pointerType>

#define InstanceCreatorInstantiationExBothPointers(Creator, Interface, Implementation, body, ...) \
	InstanceCreatorInstantiationEx(Creator, Interface, Implementation, KGL::PointerType::Unique, body, __VA_ARGS__); \
	InstanceCreatorInstantiationEx(Creator, Interface, Implementation, KGL::PointerType::Shared, body, __VA_ARGS__)

#define InstanceCreatorInstantiation(Creator, Interface, Implementation, pointerType, ...)\
	InstanceCreatorInstantiationEx(Creator, Interface, Implementation, pointerType, (KGL::PointerTypeHelper<Implementation, pointerType>::Create), __VA_ARGS__)

#define InstanceCreatorInstantiationBothPointers(Creator, Interface, Implementation, ...) \
	InstanceCreatorInstantiation(Creator, Interface, Implementation, KGL::PointerType::Unique, __VA_ARGS__); \
	InstanceCreatorInstantiation(Creator, Interface, Implementation, KGL::PointerType::Shared, __VA_ARGS__)


#define IMPLEMENT_INTERFACE_DTOR(type)\
	type::~type() = default;

#endif /* KGL_BASE_MACRO_H_INCLUDED */