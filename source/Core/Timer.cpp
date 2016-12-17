#include <Core/Timer.hpp>

namespace jej
{
    namespace
    {

#if defined _WIN32
#include <Windows.h>

        using JEJ_TIME_TYPE = __int64;

        static LARGE_INTEGER freq;
        static BOOL available = false;

        inline JEJ_TIME_TYPE _getTimeScale()
        {
            if (available)
                return freq.QuadPart;
            else
                return 1000;
        }

        inline JEJ_TIME_TYPE _getTotalTime()
        {
            LARGE_INTEGER curTime;

            if (available && QueryPerformanceCounter(&curTime))
                return curTime.QuadPart;
            else
                return GetTickCount();
        }

#elif defined ANDROID
#include <time.h>

        using JEJ_TIME_TYPE = long;


        inline JEJ_TIME_TYPE _getTimeScale()
        {
            return 1000;
        }

        inline JEJ_TIME_TYPE _getTotalTime()
        {

            timespec t;
            clock_gettime(CLOCK_MONOTONIC, &t);
            return (t.tv_sec * 1000) + (t.tv_nsec / 1000000);
        }

#endif

    }

    ////////////////////////////////////////////////////////////

    Timer::Timer(const bool p_reset) :
        m_time(0)
    {
#if defined(_WIN32)
        available = QueryPerformanceFrequency(&freq);
#endif

        if (p_reset)
            Reset();
    }

    ////////////////////////////////////////////////////////////

    Timer::~Timer()
    {

    }

    ////////////////////////////////////////////////////////////

    void Timer::Reset()
    {
        m_time = _getTotalTime();
    }

    ////////////////////////////////////////////////////////////

    float Timer::GetTime() const
    {
        JEJ_TIME_TYPE curTime = _getTotalTime();
        return float(curTime - m_time) / float(_getTimeScale());
    }

    ////////////////////////////////////////////////////////////

}