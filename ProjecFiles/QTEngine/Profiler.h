#pragma once
#include <TypeDefs.h>

namespace Profiling {

	class __declspec(dllexport) Profiler {
	public:
		static const uint MAX_FRAME_SAMPLES = 1000;
		static Profiler& getInstance();

	private:
		Profiler() {}
		Profiler(const Profiler&);
		Profiler& operator=(const Profiler&);
		static Profiler theInstance;

	#if PROFILING_ON
		const char* fileName;
		static const uint MAX_PROFILE_CATEGORIES = 20;
		uint frameIndex;
		uint categoryIndex;
		uint numUsedCategories;

		struct ProfileCategory {
			const char* name;
			float samples[MAX_FRAME_SAMPLES];
		} categories[MAX_PROFILE_CATEGORIES];
		bool currentFrameComplete() const;
		void writeData() const;
		void writeFrame(uint frameNumber) const;
		char getDelimiter(uint index) const;
		bool wrapped() const;
	#endif
	public:
	#if PROFILING_ON
		void initialize(const char* fileName);
		void shutdown();
		void newFrame();
		void addEntry(const char* category, float time);
	#else
		void initialize(const char* fileName) {}
		void shutdown() {}
		void newFrame() {}
		void addEntry(const char* category, float time) {}
	#endif
	};

#define profiler Profiling::Profiler::getInstance()
}
