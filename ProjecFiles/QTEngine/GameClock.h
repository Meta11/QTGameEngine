#pragma once
#include "Clock.h"

namespace Timing {

	class __declspec(dllexport) GameClock {
		Clock clock;
		GameClock() {}
		GameClock(const GameClock&);
		GameClock& operator=(const GameClock&);
		static GameClock instance;
	public:
		bool initialize();
		bool shutdown();
		static GameClock& getInstance();
		void newFrame();
		float dt() const;
	};
	#define gameClock Timing::GameClock::getInstance()
}


