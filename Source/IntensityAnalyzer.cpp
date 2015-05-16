#include "stdafx.h"
#include "IntensityAnalyzer.h"

IntensityAnalyzer::IntensityAnalyzer(int lower_bound, int upper_bound, int resolution)
	: Analyzer(lower_bound, upper_bound, resolution)
{

}

// Need an intensity function!
std::string IntensityAnalyzer::ConvertToBits(const double data_to_convert[], int noise_floor)
{
	return "IIIIIIII";
}