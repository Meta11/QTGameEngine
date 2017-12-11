#include "GameClock.h"

namespace Timing {

	GameClock GameClock::instance;

	bool GameClock::initialize() {
		return clock.initialize();
	}

	bool GameClock::shutdown() {
		return clock.initialize();
	}

	GameClock& GameClock::getInstance() {
		return instance;
	}

	void GameClock::newFrame() {
		return clock.lap();
	}
	float GameClock::dt() const {
		return clock.lastLapTime();
	}
}