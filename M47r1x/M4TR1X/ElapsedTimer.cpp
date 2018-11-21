#include "ElapsedTimer.h"
#include <time.h>

namespace Engine{
	namespace
	{
#if defined(_WIN32)
		typedef __int64 YAM_TIME_TYPE;
#else
		typedef long YAM_TIME_TYPE;
#endif

#if defined(_WIN32)
#include <Windows.h>

#if defined(ELAPSED_TIMER_USES_GETTICCOUNT)
		inline  YAM_TIME_TYPE getTimeScale()
		{
			return 1000;
		}

		/** Returns time in seconds */
		inline YAM_TIME_TYPE getTotalTime()
		{
			return GetTickCount();
		}
#else
		static LARGE_INTEGER pcFreq;
		static BOOL pcAvailable = false;
		static bool pcInitDone = false;

		inline  YAM_TIME_TYPE getTimeScale()
		{
			if (pcAvailable)
			{
				return pcFreq.QuadPart;
			}

			return 1000;
		}

		/** Returns time in seconds */
		inline YAM_TIME_TYPE getTotalTime()
		{
			if (!pcInitDone)
			{
				pcAvailable = QueryPerformanceFrequency(&pcFreq);
				pcInitDone = true;
			}

			LARGE_INTEGER curTime;

			if (pcAvailable && QueryPerformanceCounter(&curTime))
			{
				return curTime.QuadPart;
			}
			else
			{
				return GetTickCount();
			}
		}
#endif

#elif defined(ANDROID)

		inline  YAM_TIME_TYPE getTimeScale()
		{
			return 1000;
		}

		/** Returns time in seconds */
		inline YAM_TIME_TYPE getTotalTime()
		{
			timespec t;
			clock_gettime(CLOCK_MONOTONIC, &t);
			return (t.tv_sec * 1000) + (t.tv_nsec / 1000000);
		}
#else
		You need to have unsigned long getTime() implementation on this platform.
#endif
	}


	ElapsedTimer::ElapsedTimer()
		: m_startTime((-1))
	{
	}


	ElapsedTimer::~ElapsedTimer()
	{
	}


	void ElapsedTimer::Reset()
	{
		m_startTime = getTotalTime();
	}


	float ElapsedTimer::getTime() const
	{
		YAM_TIME_TYPE curTime = getTotalTime();

		float deltaTime = float(curTime - m_startTime) / float(getTimeScale());
		return deltaTime;
	}

}
