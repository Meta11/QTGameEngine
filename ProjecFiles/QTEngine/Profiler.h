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
		bool status;
		static const uint MAX_PROFILE_CATEGORIES = 20;
		uint frameIndex;
		uint categoryIndex;
		uint numUsedCategories;

		struct ProfileCategory {
			const char* name;
			float samples[MAX_FRAME_SAMPLES];
		} categories[MAX_PROFILE_CATEGORIES];
		void writeData() const;
		void writeFrame(uint frameNumber) const;
		char getDelimiter(uint index) const;
		bool currentFrameComplete() const;
		bool wrapped() const;
#endif //PROFILING_ON
	public:
#if PROFILING_ON
		void initialize(const char* fileName);
		void shutdown();
		void newFrame();
		void addEntry(const char* category, float time);
		void checkStatus(bool* status) const;
		void checkForDuplicateCategory(const char* category);
#else
		void initialize(const char* fileName) {}
		void shutdown() {}
		void newFrame() {}
		void addEntry(const char* category, float time) {}
		bool checkIsGood(bool* status) const {}
		void checkForDuplicateCategory(const char* category) {}
#endif //PROFILING_ON	
	};

#define profiler Profiling::Profiler::getInstance()
}
