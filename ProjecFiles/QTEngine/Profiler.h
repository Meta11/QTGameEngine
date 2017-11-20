#pragma once

class __declspec(dllexport) Profiler {

	const char* fileName;
	static const unsigned int MAX_FRAME_SAMPLES = 200;
	static const unsigned int MAX_PROFILE_CATEGORIES = 15;
	unsigned int frameIndex;
	unsigned int categoryIndex;
	unsigned int numUsedCategories;
		
	struct ProfileCategory{
		const char* name;
		float samples[MAX_FRAME_SAMPLES];
	} categories[MAX_PROFILE_CATEGORIES];
	char getDelimiter(int index) const;

public:
	void initialize(const char* fileName);
	void shutdown();
	void newFrame();
	void addEntry(const char* category, float time);
};

