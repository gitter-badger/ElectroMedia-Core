#include "stdafx.h"
#include "SignalProcessingAlgorithms.h"

// SignalProcessingAlgorithm Constructor
// ---
// ...
SignalProcessingAlgorithm::SignalProcessingAlgorithm()
    : lowerBound_(0), upperBound_(0), bits_(8)
{ /* - No op - */ }

// SignalProcessingAlgorithm Destructor
// ---
// If we have stuff to dealloc, do it here
SignalProcessingAlgorithm::~SignalProcessingAlgorithm()
{ /* - No op - */ }

// setbounds(int,int)
// ---
// Redeclares the lower and upper bounds as dictated by the FrequencyRangeProfile
void SignalProcessingAlgorithm::setBounds(const int lower, const int upper)
{
    lowerBound_ = lower;
    upperBound_ = upper;
}

// BASE
// convertToBits(double*, int)
// ---
// Main variant of the processor.convertToBits(); function. This takes the array of
// data doubles and performs some algorithm (as defined by derived/child classes)
// to return a string/bytestream. In this main variety, the algorithm merely checks
// for signficant (above noise floor) frequencies, and marks the indices as high.
// 
// Result is by default Big Endian, but this can be changed through config by
// setting OUTPUT_IS_BIG_ENDIAN to false in "stdafx.h"
std::string SignalProcessingAlgorithm::convertToBits(const double* dataToConvert, int noiseFloor) 
{	
    auto bitLength = (upperBound_ - lowerBound_) / bits_;

    auto preparedData = preProcessForConversion(dataToConvert);
    auto flooredData = applyNoiseFloor(preparedData, noiseFloor);
    auto resultingBits = evaluateBits(flooredData, bitLength);

    // By default, this result is Big Endian due to the nature of frequencies increasing 
    // left-to-right. The nature of the output can be altered by changing the 
    // OUTPUT_IS_BIG_ENDIAN setting in "stdafx.h" which will then reverse the output.
    if(OUTPUT_IS_BIG_ENDIAN)
    {
        return bigEndianConvert(resultingBits);
    }

    return littleEndianConvert(resultingBits);
}

double* SignalProcessingAlgorithm::preProcessForConversion(const double* dataToConvert)
{
    // Nothing should really happen in the parent method
    auto returnVal = (double*)dataToConvert;
    return returnVal;
}

double checkAgainstNoiseFloor(double frequency, int noiseFloor)
{
    if(frequency < noiseFloor)
    {
        return 0;
    }

    return frequency;
}

double* SignalProcessingAlgorithm::applyNoiseFloor(const double* preProcesedData, int noiseFloor)
{
    auto processingData = (double*)preProcesedData;

    for(int freqIndex = lowerBound_; freqIndex < upperBound_; freqIndex++)
    {
        checkAgainstNoiseFloor(processingData[freqIndex],noiseFloor);
    }

    return processingData;
}

std::string SignalProcessingAlgorithm::checkBit(bool bitToCheck)
{
    if(bitToCheck)
    {
        return "1";
    }

    return "0";
}

std::string SignalProcessingAlgorithm::bigEndianConvert(const bool* processedBits)
{
    auto outputString = (std::string)"";

    for(int bit_ = 0; bit_ < bits_; bit_++)
    {
        outputString.append( checkBit(processedBits[bit_]) );
    }

    return outputString;
}

std::string SignalProcessingAlgorithm::littleEndianConvert(const bool* processedBits)
{
    auto outputString = (std::string)"";

    for(int bit_ = bits_; bit_ >= 0; bit_--)
    {
        outputString.append( checkBit( processedBits[bit_] ) );
    }

    return outputString;
}

// -- Hill Effect -- //
bool* SPAHillEffect::evaluateBits(const double* processedData, const int bitLength)
{	
    double maxAmplitude = -1, maxIndex = -1;

    // Basic algorithm: Iterates through the bits, using a scalar value to interpolate
    // between frequencies (according to the boundaries set by owning FRP)
    for(int bit_ = lowerBound_; bit_ < upperBound_; bit_++)
    {
        double currentAmplitude = processedData[bit_];

        if(currentAmplitude > maxAmplitude)
        {
            maxAmplitude = currentAmplitude;
            maxIndex = bit_;
        }
    }
}

// Need an intensity function!
std::string SPAIntensity::convertToBits(const double* dataToConvert, int noiseFloor)
{	
    return "IIIIIIII";
}