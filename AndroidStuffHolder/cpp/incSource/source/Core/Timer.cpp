#include <Core/Timer.hpp>

namespace jej
{
	namespace
	{

#if defined _WIN32

#include <Windows.h>
		typedef __int64 JEJ_TIME_TYPE;

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

		typedef long JEJ_TIME_TYPE;


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

	Timer::Timer() :
		m_time(0)
	{
#if defined(_WIN32)
		available = QueryPerformanceFrequency(&freq);
#endif
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

	Timer& Timer::GetInstance(const bool p_reset)
	{
		static Timer instance;

		if (p_reset)
			instance.Reset();

		return instance;
	}

}