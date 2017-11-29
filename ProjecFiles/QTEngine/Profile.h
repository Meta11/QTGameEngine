#pragma once
#if PROFILING_ON
#include <Clock.h>
#endif //PROFILING_ON

namespace Profiling {

	class __declspec(dllexport) Profile {
#if PROFILING_ON
		const char* category;
		Timing::Clock clock;
#endif //PROFILING_ON
	public:
#if PROFILING_ON
		Profile(const char* category);
		~Profile();
#else
		Profile(const char* category) {}
		~Profile{}
#endif //PROFILING_ON
	};
}
#if PROFILING_ON
#define PROFILE(category) Profiling::Profile p(category)
#else
#define PROFILE(category) 
#endif //PROFILING_ON