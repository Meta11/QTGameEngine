#include "Profiler.h"
#ifdef PROFILING_ON
#include <fstream>
#endif // PROFILING_ON

namespace Profiling {

	Profiler Profiler::theInstance;

	Profiler& Profiler::getInstance() {
		return theInstance;
	}

#ifdef PROFILING_ON

	static std::ofstream outStream;
	using std::ios;

	void Profiler::initialize(const char* fileName) {
		this->fileName = fileName;
		status = true;
		frameIndex = -1;
		categoryIndex = 0;
		numUsedCategories = 0;
	}

	void Profiler::shutdown() {
		writeData();
	}

	void Profiler::newFrame() {
		frameIndex++;
		categoryIndex = 0;
	}

	void Profiler::addEntry(const char* category, float time) {

		ProfileCategory& pc = categories[categoryIndex];
		if (frameIndex == 0) {
			pc.name = category;
			numUsedCategories++;
		}
		categoryIndex++;
		pc.samples[frameIndex % MAX_FRAME_SAMPLES] = time;
		checkForDuplicateCategory(category);
	}

	void Profiler::checkStatus(bool* status) const {
		*status = status;
	}

	char Profiler::getDelimiter(uint index) const {
		return ((index + 1) < numUsedCategories) ? ',' : '\n';
	}

	bool Profiler::wrapped() const {
		return frameIndex >= MAX_FRAME_SAMPLES && frameIndex != -1;
	}

	void Profiler::writeData() const {
		outStream.open(fileName, ios::trunc);
		//headers
		for (uint i = 0; i < numUsedCategories; i++) {
			outStream << categories[i].name;
			outStream << getDelimiter(i);
		}

		uint endIndex;
		uint startIndex;
		if (wrapped()) {
			endIndex = frameIndex % MAX_FRAME_SAMPLES;
			startIndex = (endIndex + 1) % MAX_FRAME_SAMPLES;
			while (startIndex != endIndex) {
				writeFrame(startIndex);
				startIndex = (startIndex + 1) % MAX_FRAME_SAMPLES;
			}
			if(currentFrameComplete())
				writeFrame(startIndex);
		}
		else {
			uint numActualFrames = frameIndex;
			if (currentFrameComplete())
				numActualFrames++;
			startIndex = 0;
			endIndex = numActualFrames;
			while (startIndex < endIndex)
				writeFrame(startIndex++);
		}
		outStream.close();
	}

	bool Profiler::currentFrameComplete() const {
		return categoryIndex == numUsedCategories;
	}

	void Profiler::writeFrame(uint frameNumber) const {
		for (uint cat = 0; cat < numUsedCategories; cat++) {
			outStream << categories[cat].samples[frameNumber];
			outStream << getDelimiter(cat);
		}
	}

	void Profiler::checkForDuplicateCategory(const char* category) {
		for (uint i = 0; i < categoryIndex; i++) {
			status &= (strcmp(categories[i].name, category) != 0);
		}
	}

#endif
}

