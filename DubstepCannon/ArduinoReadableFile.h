#include "stdafx.h"
#include "FrequencyRangeProfile.h"

class ArduinoReadableFile
{
public:
	// Constructors / Destructors
	ArduinoReadableFile(char* nameOfARF);
	~ArduinoReadableFile();
	
	// Public methods interfacing with ofstream
	bool addFrequencyRange(double lowerFrequency, double upperFrequency, int adjustment);
	void setMode(int newMode);
	bool isTextWritable();
	void write(std::string stringToWrite);
	void write(int intToWrite);
	void write(double* dataToWrite);
	void close();

	// Enumerated Lists
	static const enum writeMode {MODE_TEXT, MODE_ARDUINO, MODE_ARDUINO_MEGA};

private:
	std::ofstream arfStream;
	int mode_, numberOfOutputs_;
	size_t numberOfFrequencyRanges_;
	FrequencyRangeProfile* frequencyRanges_;
};