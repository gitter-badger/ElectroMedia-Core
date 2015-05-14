#include "stdafx.h"
#include "IntensityAnalyzer.h"

IntensityAnalyzer::IntensityAnalyzer(int lowerBound, int upperBound, int resolution)
	: Analyzer(lowerBound, upperBound, resolution)
{

}

// Need an intensity function!
std::string IntensityAnalyzer::ConvertToBits(const double dataToConvert[], int noiseFloor)
{
	return "IIIIIIII";
}