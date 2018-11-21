#ifndef ELAPSEDTIMER_H
#define ELAPSEDTIMER_H

#include "Object.h"


namespace Engine{
	class ElapsedTimer : public Object

	{
	public:
		ElapsedTimer();
		virtual ~ElapsedTimer();

		void Reset();			// ajastimen nollaus
		float getTime() const;	// palauttaa ajan sekunteina
	private:
#if defined(_WIN32)
		typedef __int64 YAM_TIME_TYPE;
#else
		typedef long YAM_TIME_TYPE;
#endif
		YAM_TIME_TYPE m_startTime;
	};
}

#endif
