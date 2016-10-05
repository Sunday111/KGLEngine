#ifndef KGL_BASE_MACRO_H_INCLUDED
#define KGL_BASE_MACRO_H_INCLUDED

#define SAFE_DELETE(ptr) { if(ptr != nullptr) delete ptr; }
#define SAFE_ARRAY_DELETE(ptr) { if(ptr != nullptr) delete [] ptr; }

#endif /* KGL_BASE_MACRO_H_INCLUDED */