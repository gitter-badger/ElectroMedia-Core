#include "stdafx.h"

#ifndef CoreMathDefinition
#define CoreMathDefinition

static class CoreMath
{
public:
	static double AlignFrequency(double frequency);

	// Basic methods which convert an integer index to a frequency value, or vice versa
	static int ConvertFrequencyToInt(double frequencyBand);
	static double ConvertIntToFrequency(int index);

	// Used to calculate a dynamic noise floor, taking fluctuations in signal noise
	// and amplitude changes into consideration. Returns an integer value which 
	// corresponds to noise floor amplitude
	//int calculateDynamicNoiseFloor(vector<T> data, int lowerBound, int upperBound);

	// NEED NOTES
	static double CalculateIntensityScalar(double frequency);

	// Pipes out a line of text to cerr if and only if DEBUG_ENABLED == true
	static void Debug(std::string debugComment);

	static std::string GetPath(char* basePath);
};

#endif