#include "Clock.h"

namespace Timing {

	bool Clock::initialize() {
		//Numero de ticks por segundo
		bool b = QueryPerformanceFrequency(&timeFrequency);
		if (!b) 
			return false;
		//Numero de ticks del primer frame
		return QueryPerformanceCounter(&lastStartTime);
	}

	bool Clock::shutdown() { return true; }

	void Clock::start() {
		QueryPerformanceCounter(&lastStartTime);
	}

	void Clock::stop() {
		LARGE_INTEGER thisTime;
		//Numero de ticks del siguiente frame
		QueryPerformanceCounter(&thisTime);
		//Encontramos la diferencia entre el primer frame y el siguiente
		LARGE_INTEGER delta;
		delta.QuadPart = thisTime.QuadPart - lastStartTime.QuadPart;
		deltaTime = (float)delta.QuadPart / timeFrequency.QuadPart;
		//lastStartTime.QuadPart = thisTime.QuadPart;
	}

	void Clock::lap() {
		stop();
		start();
	}

	float Clock::timeElapsedLastFrame() const {
		return deltaTime;
	}

}