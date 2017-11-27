#pragma once
#include <Clock.h>

namespace Profiling {

	class __declspec(dllexport) Profile {
		const char* category;
		Timing::Clock clock;
	public:
		Profile(const char* category);
		~Profile();
	};
}