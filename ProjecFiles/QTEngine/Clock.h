#pragma once
#include <Windows.h>

namespace Timing {

	class __declspec(dllexport) Clock {

		LARGE_INTEGER timeFrequency;
		LARGE_INTEGER lastStartTime;
		LARGE_INTEGER deltaLastFrame;
		float deltaTime;

	public:
		bool initialize();
		bool shutdown();
		void start();
		void stop();
		void lap();
		float lastLapTime() const;
	};

}

