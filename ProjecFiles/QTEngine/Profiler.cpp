#include "Profiler.h"
#ifdef PROFILING_ON
Profiler Profiler::theInstance;

Profiler& Profiler::getInstance() {
	return theInstance;
}

#include <fstream>

static std::ofstream outStream;
using std::ios;

void Profiler::initialize(const char* fileName) {
	this->fileName = fileName;
	frameIndex = -1;
	categoryIndex = 0;
	numUsedCategories = 0;
}

void Profiler::shutdown() {
	writeData();
}

char Profiler::getDelimiter(unsigned int index) const {
	return ((index + 1) < numUsedCategories ? ',' : '\n');
}

bool Profiler::wrapped() const {
	return frameIndex >= MAX_FRAME_SAMPLES && frameIndex != -1;
}

void Profiler::writeData() const {
	outStream.open(fileName, ios::trunc);
	//headers
	for (unsigned int i = 0; i < numUsedCategories; i++) {
		outStream << categories[i].name;
		outStream << getDelimiter(i);
	}

	unsigned int endIndex;
	unsigned int startIndex;
	if (wrapped()) {
		endIndex = frameIndex % MAX_FRAME_SAMPLES;
		startIndex = (endIndex + 1) % MAX_FRAME_SAMPLES;
		while (startIndex != endIndex) {
			writeFrame(startIndex);
			startIndex = (startIndex + 1) % MAX_FRAME_SAMPLES;
		}
		writeFrame(startIndex);
	}
	else {
		unsigned int numActualFrames = frameIndex;
		if (currentFrameComplete())
			numActualFrames++;
		startIndex = 0;
		endIndex = numActualFrames;
		while (startIndex < endIndex)
			writeFrame(startIndex++);
	}
	outStream.close();
}

void Profiler::newFrame() {
	frameIndex++;
	categoryIndex = 0;
}

void Profiler::addEntry(const char* category, float time) {

	ProfileCategory& pc = categories[categoryIndex++];
	if (frameIndex == 0) {
		pc.name = category;
		numUsedCategories++;
	}
	pc.samples[frameIndex % MAX_FRAME_SAMPLES] = time;
}

void Profiler::writeFrame(unsigned int frameNumber) const {
	for (unsigned int cat = 0; cat < numUsedCategories; cat++) {
		outStream << categories[cat].samples[frameNumber];
		outStream << getDelimiter(cat);
	}
}

bool Profiler::currentFrameComplete() const {
	return categoryIndex == numUsedCategories;
}

#endif
