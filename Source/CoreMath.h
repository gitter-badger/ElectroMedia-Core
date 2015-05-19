#include "stdafx.h"
#include "EmcSettings.h"

#ifndef EMC_CoreMath_H_
#define EMC_CoreMath_H_

static class CoreMath
{
public:

	// Basic methods which convert an integer index to a frequency value, or vice versa
	static int ConvertFrequencyToInt(double frequency_bound);
	static double ConvertIntToFrequency(int index);

	// Used to calculate a dynamic noise floor, taking fluctuations in signal noise
	// and amplitude changes into consideration. Returns an integer value which 
	// corresponds to noise floor amplitude
	//int calculateDynamicNoiseFloor(vector<T> data, int lowerBound, int upperBound);

	// NEED NOTES
	static double CalculateIntensityScalar(double frequency);

	// Pipes out a line of text to cerr if and only if DEBUG_ENABLED == true
	static void Debug(std::string debug_comment);

	static std::string GetPath(char* base_path);
	static std::string GetFilenameWithoutExtension(std::string full_path);
	static std::string ChangeFileExtension(std::string full_path, std::string new_extension);
};

#endif