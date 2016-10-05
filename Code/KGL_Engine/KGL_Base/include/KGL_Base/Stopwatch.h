#ifndef KGL_BASE_STOPWATCH_H_INCLUDED
#define KGL_BASE_STOPWATCH_H_INCLUDED

#include <cstdint>

namespace KGL {

class Stopwatch
{
public:
    Stopwatch();

    Stopwatch(const Stopwatch&) = default;

    int64_t ElapsedMs() const;

    void Start();

    Stopwatch& operator=(const Stopwatch&) = default;

private:
    int64_t m_origin;
};

}

#endif /*KGL_BASE_STOPWATCH_H_INCLUDED*/