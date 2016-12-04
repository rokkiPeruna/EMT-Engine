#ifndef JEJ_TIMER_HPP
#define JEJ_TIMER_HPP



namespace jej
{
	class Timer
	{
    private:

#if defined _WIN32
        typedef __int64 JEJ_TIME_TYPE;
#elif defined ANDROID
        typedef long JEJ_TIME_TYPE;
#endif
        JEJ_TIME_TYPE m_time;

		//Constructor
		Timer();

	public:
		
		//Disabled copy-constructors
		Timer(const Timer&) = delete;
		void operator=(const Timer&) = delete;

		//Destructor
		~Timer();

		//Reset timer
		void Reset();

		//Return elapsed time since last reset
		float GetTime() const;

		static Timer& GetInstance(const bool p_reset = false);

	};
}

#endif