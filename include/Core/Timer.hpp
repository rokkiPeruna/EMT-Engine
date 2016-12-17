#ifndef JEJ_TIMER_HPP
#define JEJ_TIMER_HPP

//For nocopy
#include <Core/Settings.hpp>

namespace jej
{
    class Timer
    {
    private:

#if defined _WIN32
        using  JEJ_TIME_TYPE = __int64;
#elif defined ANDROID
        using JEJ_TIME_TYPE = long;
#endif
        JEJ_TIME_TYPE m_time;

    public:

        //Constructor
        //Reset timer upon creating
        Timer(const bool p_reset = false);

        //Disabled copy-constructors
        NOCOPY(Timer);

        //Destructor
        ~Timer();

        //Reset timer
        void Reset();

        //Return elapsed time since last reset
        float GetTime() const;

    };
}

#endif