#include "stdafx.h"
#include "Constants.h"
#include "CoreMath.h"

// int = convertFrequencyToInt(double)
// double = convertIntToFrequency(int)
// ---
// Converts an integer index into its appropriate double frequency identifier or
// vice versa. The OFFSET and SCALAR values are defined in stdafx.h and were
// determined through the use of a calibration curve
int CoreMath::ConvertFrequencyToInt(double frequency_bound)
{
	return int((frequency_bound - Settings.kBoundaryConversionOffset) / Settings.kBoundaryConversionScalar);
}

double CoreMath::ConvertIntToFrequency(int index)
{
	return int((index * Settings.kBoundaryConversionScalar + Settings.kBoundaryConversionOffset));
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
void CoreMath::Debug(std::string debug_comment)
{
	if (Settings.debug_mode_)
    {
		std::cerr << debug_comment << "\n";
    }
}

std::string CoreMath::GetPath(char* base_path)
{
	auto path = (std::string)base_path;
	auto executable_location = ((std::string)path).find("EMC.exe");
	return std::string(path.begin(), executable_location + path.begin());
}

std::string CoreMath::GetFilenameWithoutExtension(std::string full_path)
{
	auto full_argument = full_path;
	auto extension_location = full_argument.find(".");

	// Protection for noninclusion of extension
	if (extension_location > full_argument.size())
	{
		extension_location = full_argument.size();
	}

	return std::string(full_argument.begin(), full_argument.begin() + extension_location);
}

std::string CoreMath::ChangeFileExtension(std::string full_path, std::string new_extension)
{
	return CoreMath::GetFilenameWithoutExtension(full_path) + new_extension;
}