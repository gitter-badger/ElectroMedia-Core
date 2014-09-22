#include "stdafx.h"
#include "CommonOperations.h"

// int = convertFrequencyToInt(double)
// double = convertIntToFrequency(int)
// ---
// Converts an integer index into its appropriate double frequency identifier or
// vice versa. The OFFSET and SCALAR values are defined in stdafx.h and were
// determined through the use of a calibration curve
int convertFrequencyToInt(double frequencyBand)
{ 
	return int((frequencyBand - BOUNDARY_CONVERSION_OFFSET) / BOUNDARY_CONVERSION_SCALAR); 
}

double convertIntToFrequency(int index)
{
	return double(index * BOUNDARY_CONVERSION_SCALAR + BOUNDARY_CONVERSION_OFFSET);
}

// int = calculateDynamicNoiseFloor(double*, int, int)
// ---
// Calculates a dynamic noise floor based upon the amplitudes of the data array within
// specific indices, and then returns the value of said noise floor. This method 
// accomplishes dynamicity by taking a percentage (as defined in "stdafx.h") of the
// maximum within the dataset and returning the higher value between the dynamic and
// static noise floors
// ...
// Performance: O(n)
int calculateDynamicNoiseFloor(double* data, int lowerBound, int upperBound)
{
	int dynamicNoiseFloor_ = -1, 
		preNFMaximum_ = 0;

	// Iterate through the frequency band and determine the maximum in the data set
	for(int i = lowerBound; i < upperBound; i++)
	{
		preNFMaximum_ = (data[i] > preNFMaximum_ ? data[i] : preNFMaximum_ );
	}

	// Set the dynamic noise floor value to be equal to a certain percentage of the maximum if it is higher
	// than the default noise floor of 50 A
	dynamicNoiseFloor_ = preNFMaximum_ * (double(NOISE_FLOOR_PCT) / 100);

	// Compare the dynamic and static Noise Floors, then return the greater of the two
	return (dynamicNoiseFloor_ > NOISE_FLOOR ? dynamicNoiseFloor_ : NOISE_FLOOR);
}

// NEED NOTES; Also probably broken
double calculateIntensityScalar(double frequency)
{
	return (std::pow(0.5 * frequency + 10, 1/3)) - 1.15;
}

// debug(std::string)
// ---
// Pipes a line of text into the std::cerr stream if DEBUG_ENABLED is set to true
// in stdafx.h.
void debug(std::string debugComment)
{
	if(DEBUG_ENABLED)
	{
		std::cerr << debugComment << endl;
	}
}