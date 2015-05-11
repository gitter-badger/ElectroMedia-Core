#include "stdafx.h"
#include "Constants.h"
#include "CoreMath.h"

// int = convertFrequencyToInt(double)
// double = convertIntToFrequency(int)
// ---
// Converts an integer index into its appropriate double frequency identifier or
// vice versa. The OFFSET and SCALAR values are defined in stdafx.h and were
// determined through the use of a calibration curve
int CoreMath::ConvertFrequencyToInt(double frequencyBand)
{ 
    return int((frequencyBand - BOUNDARY_CONVERSION_OFFSET) / BOUNDARY_CONVERSION_SCALAR); 
}

double CoreMath::ConvertIntToFrequency(int index)
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


// NEED NOTES; Also probably broken
double CoreMath::CalculateIntensityScalar(double frequency)
{
    return (std::pow(0.5 * frequency + 10, 1/3)) - 1.15;
}

// CoreMath::Debug(std::string)
// ---
// Pipes a line of text into the std::cerr stream if DEBUG_ENABLED is set to true
// in stdafx.h.
void CoreMath::Debug(std::string debugComment)
{
    if(DEBUG_ENABLED)
    {
        std::cerr << debugComment << "\n";
    }
}


