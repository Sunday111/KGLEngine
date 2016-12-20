#include <chrono>

#include <KGL_Base/Stopwatch.h>

namespace KGL {

static int64_t s_GetTickMs()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

Stopwatch::Stopwatch() :
m_origin(s_GetTickMs())
{

}

int64_t Stopwatch::ElapsedMs() const
{
    return s_GetTickMs() - m_origin;
}

void Stopwatch::Start()
{
    m_origin = s_GetTickMs();
}

}
