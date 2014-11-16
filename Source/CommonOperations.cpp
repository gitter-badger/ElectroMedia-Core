#include "stdafx.h"
#include "CommonOperations.h"
#include <thread>
#include <chrono>

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
        std::cerr << debugComment << "\n";
    }
}

void readARF(char filename[])
{
    std::string fullArgument = filename;
    auto extensionLocation = fullArgument.find(".");

    // Protection for noninclusion of extension
    if (extensionLocation > fullArgument.size())
    {
        extensionLocation = fullArgument.size();
    }

    auto nameWithoutExtension = std::string(fullArgument.begin(), fullArgument.begin() + extensionLocation);
    std::string arFileName = nameWithoutExtension + AR_FILE_EXTENSION;

    std::ifstream visualizationFile(arFileName);
    if (visualizationFile.is_open())
    {
        std::string line;
        auto start = std::chrono::high_resolution_clock::now();
        while (std::getline(visualizationFile, line))
        {
            cout << line << "\n";
            std::this_thread::sleep_until(start + std::chrono::microseconds(45000));
            start = std::chrono::high_resolution_clock::now();
            //while (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() < 46447);
        }
    }
}
