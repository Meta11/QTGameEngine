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
		//Numero de ticks del siguiente frame
		QueryPerformanceCounter(&lastStartTime);
	}

	void Clock::stop() {
		//Encontramos la diferencia entre el primer frame y el siguiente
		LARGE_INTEGER thisTime;
		QueryPerformanceCounter(&thisTime);
		LARGE_INTEGER delta;
		delta.QuadPart = thisTime.QuadPart - lastStartTime.QuadPart;
		deltaTime = (float)delta.QuadPart / timeFrequency.QuadPart;
		deltaLastLap.QuadPart = thisTime.QuadPart;
	}

	void Clock::lap() {
		stop();	
		start();
	}

	float Clock::lastLapTime() const {
		return deltaTime;
	}

}