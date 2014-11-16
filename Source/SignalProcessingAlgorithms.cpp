#include "stdafx.h"
#include "SignalProcessingAlgorithms.h"

// SignalProcessingAlgorithm Constructor
// ---
// ...
SignalProcessingAlgorithm::SignalProcessingAlgorithm()
    : lowerBound_(0), upperBound_(0), bits_(4)
{ /* - No op - */ }

SignalProcessingAlgorithm::SignalProcessingAlgorithm(int numberOfBits)
    : lowerBound_(0), upperBound_(0)
{
    bits_ = numberOfBits;
}

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
std::string SignalProcessingAlgorithm::convertToBits(UniqueDataSet& dataToConvert, int noiseFloor)
{
    preProcessForConversion(dataToConvert);
    applyNoiseFloor(dataToConvert, noiseFloor);
    auto resultingBits = evaluateBits(dataToConvert);

    // By default, this result is Big Endian due to the nature of frequencies increasing 
    // left-to-right. The nature of the output can be altered by changing the 
    // OUTPUT_IS_BIG_ENDIAN setting in "stdafx.h" which will then reverse the output.
    if(OUTPUT_IS_BIG_ENDIAN)
    {
        return bigEndianConvert(resultingBits);
    }
    return littleEndianConvert(resultingBits);
}

void SignalProcessingAlgorithm::preProcessForConversion(UniqueDataSet& dataToConvert)
{
    // Nothing should really happen 
}

double checkAgainstNoiseFloor(double frequency, int noiseFloor)
{
    if(frequency < noiseFloor)
    {
        return 0;
    }

    return frequency;
}

void SignalProcessingAlgorithm::applyNoiseFloor(UniqueDataSet& preProcesedData, int noiseFloor)
{
    // Replace with iterator
    DataSetIterator it = preProcesedData->begin();
    while (it != preProcesedData->end())
    {
        *it = checkAgainstNoiseFloor(*it, noiseFloor);
        ++it;
    }
}

dynamic_bitset<> SignalProcessingAlgorithm::evaluateBits(UniqueDataSet& processedData)
{
    auto bitLength = (upperBound_ - lowerBound_) / bits_;
    auto currentBitIndex = (int) 0;
    dynamic_bitset<> outBits(bits_);

    for (int bitIndex = 0; bitIndex < bits_; bitIndex++)
    {
        outBits[bitIndex] = false;
        for (int interIndex = 0; interIndex < bitLength; interIndex++)
        {
            currentBitIndex = lowerBound_ + (bitIndex * bitLength) + interIndex;
            if (processedData->at(currentBitIndex) > 0)
            {
                outBits[bitIndex] = true;
                break;
            }
        }
    }

    return outBits;
}


std::string SignalProcessingAlgorithm::checkBit(bool bitToCheck)
{
    if(bitToCheck)
    {
        return "1";
    }

    return "0";
}

std::string SignalProcessingAlgorithm::bigEndianConvert(dynamic_bitset<>& processedBits)
{
    auto outputString = (std::string)"";

    for (int bit_ = 0; bit_ < processedBits.size(); bit_++)
    {
        outputString.append( checkBit(processedBits[bit_]) );
    }

    return outputString;
}

std::string SignalProcessingAlgorithm::littleEndianConvert(dynamic_bitset<>& processedBits)
{
    auto outputString = (std::string)"";

    for (int bit_ = processedBits.size()-1; bit_ >= 0; bit_--)
    {
        outputString.append( checkBit( processedBits[bit_] ) );
    }

    return outputString;
}

// -- Hill Effect -- //
dynamic_bitset<> SPAHillEffect::evaluateBits(UniqueDataSet& processedData, const int bitLength)
{	
    double maxAmplitude = -1, maxIndex = -1;

    // Basic algorithm: Iterates through the bits, using a scalar value to interpolate
    // between frequencies (according to the boundaries set by owning FRP)
    for(int bit_ = lowerBound_; bit_ < upperBound_; bit_++)
    {
        double currentAmplitude = processedData->at(bit_);

        if(currentAmplitude > maxAmplitude)
        {
            maxAmplitude = currentAmplitude;
            maxIndex = bit_;
        }
    }


    return dynamic_bitset<>(0);
}

// Need an intensity function!
std::string SPAIntensity::convertToBits(const double dataToConvert[], int noiseFloor)
{	
    return "IIIIIIII";
}