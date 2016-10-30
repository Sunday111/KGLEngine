#ifndef KGL_CORE_RTTI_H_INCLUDED
#define KGL_CORE_RTTI_H_INCLUDED

#include <KGL_Core/TypeRegistry.h>

#include <cassert>
#include <vector>
#include <unordered_map>


namespace KGL { namespace Core {

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

} }


#endif