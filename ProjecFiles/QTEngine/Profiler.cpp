#include "Profiler.h"
#include <fstream>

using std::ofstream;
using std::ios;

void Profiler::initialize(const char* fileName) {
	this->fileName = fileName;
	frameIndex = -1;
	categoryIndex = 0;
	numUsedCategories = 0;
}

void Profiler::shutdown() {

	ofstream outStream(fileName, ios::trunc);
	//headers
	for (int i = 0; i < numUsedCategories; i++) {
		outStream << categories[i].name;
		outStream << getDelimiter(i);
	}

	unsigned int numactualFrames = frameIndex;
	if (categoryIndex == numUsedCategories)
		numactualFrames++;

	for (unsigned int frame = 0; frame < numactualFrames; frame++) {
		for (unsigned int cat = 0; cat < categoryIndex; cat++) {
			outStream << categories[cat].samples[frame];
			outStream << getDelimiter(cat);
		}
	}
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
	pc.samples[frameIndex] = time;
}

char Profiler::getDelimiter(int index) const {
	return ((index + 1) < numUsedCategories ? ',' : '\n');
}
