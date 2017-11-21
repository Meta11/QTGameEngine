#pragma once

class __declspec(dllexport) Profiler {

	const char* fileName;
	static const unsigned int MAX_FRAME_SAMPLES = 1000;
	static const unsigned int MAX_PROFILE_CATEGORIES = 20;
	unsigned int frameIndex;
	unsigned int categoryIndex;
	unsigned int numUsedCategories;
		
	struct ProfileCategory{
		const char* name;
		float samples[MAX_FRAME_SAMPLES];
	} categories[MAX_PROFILE_CATEGORIES];
	bool currentFrameComplete() const;
	void writeData() const;
	void writeFrame(unsigned int frameNumber) const;
	char getDelimiter(int index) const;
	bool wrapped() const;

public:
	void initialize(const char* fileName);
	void shutdown();
	void newFrame();
	void addEntry(const char* category, float time);
};

