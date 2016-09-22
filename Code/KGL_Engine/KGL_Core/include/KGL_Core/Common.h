#ifndef KGL_CORE_COMMON_H_INCLUDED
#define KGL_CORE_COMMON_H_INCLUDED

//Set compiler dependent semantics for library visibility 
#if defined(MSVC)
	//Microsoft
	#if defined KGL_CORE_SHARED
		#define KGL_CORE_API __declspec(dllexport)
	#else
		#define KGL_CORE_API __declspec(dllimport)
	#endif
#elif defined(GNU)
	//GCC
	#if defined KGL_CORE_SHARED
		#define KGL_CORE_API __attribute__((visibility("default")))
	#else
		#define KGL_CORE_API
	#endif
#else
	//not implemented
	#pragma warning Not implemented for this compiler
#endif

#ifdef KGL_CORE_SHARED
	#define KGL_CORE EXPORT
#else
	#define KGL_CORE IMPORT
#endif /* KGL_CORE_SHARED */


#endif /* KGL_CORE_COMMON_H_INCLUDED */