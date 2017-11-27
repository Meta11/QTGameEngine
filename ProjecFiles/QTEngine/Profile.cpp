#include "Profile.h"
#include "Profiler.h"

using Timing::Clock;

namespace Profiling {

	Profile::Profile(const char* category): category(category) {
		Clock clock;
		clock.initialize();
		clock.start();
	}
	Profile::~Profile() {
		clock.stop();
		profiler.addEntry(category, clock.lastLapTime());
	}
}

