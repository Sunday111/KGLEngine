#ifndef KGL_CORE_RTTI_H_INCLUDED
#define KGL_CORE_RTTI_H_INCLUDED

#include <KGL_Core/TypeRegistry.h>

#include <cassert>
#include <vector>
#include <unordered_map>


namespace KGL { namespace Core { namespace Rtti
{

template<typename Head, typename... Tail>
struct RttiHelper
{
    static void CreateIdArray(std::vector<int>& out)
    {
        out.push_back(Head::TypeId());
        RttiHelper<Tail ...>::CreateIdArray(out);
    }
};


template<typename Head>
struct RttiHelper<Head>
{
    static void CreateIdArray(std::vector<int>& out)
    {
        out.push_back(Head::TypeId());
    }
};

struct _general {};
struct _special : public _general {};
template<typename> struct _int { using type = int; };

template<typename T,
	typename _int<decltype(T::LoadFromFile)>::type = 0>
	TypeInfo::CreateFromFileFn GetLoadFromFileMethod(_special)
{
	return &T::LoadFromFile;
}

template<typename T>
TypeInfo::CreateFromFileFn GetLoadFromFileMethod(_general)
{
	return nullptr;
}

} } }


#endif