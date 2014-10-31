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
std::string SignalProcessingAlgorithm::convertToBits(dataSet& dataToConvert, int noiseFloor) 
{
    auto preparedData = preProcessForConversion(dataToConvert);
    auto flooredData = applyNoiseFloor(preparedData, noiseFloor);
    auto resultingBits = evaluateBits(flooredData);

    // By default, this result is Big Endian due to the nature of frequencies increasing 
    // left-to-right. The nature of the output can be altered by changing the 
    // OUTPUT_IS_BIG_ENDIAN setting in "stdafx.h" which will then reverse the output.
    if(OUTPUT_IS_BIG_ENDIAN)
    {
        return bigEndianConvert(resultingBits);
    }

    return littleEndianConvert(resultingBits);
}

dataSet SignalProcessingAlgorithm::preProcessForConversion(dataSet& dataToConvert)
{
    // Nothing should really happen in the parent method]
    return dataSet(dataToConvert);
}

double checkAgainstNoiseFloor(double frequency, int noiseFloor)
{
    if(frequency < noiseFloor)
    {
        return 0;
    }

   // cout << "Higher than noise floor!\n";
    return frequency;
}

dataSet SignalProcessingAlgorithm::applyNoiseFloor(dataSet& preProcesedData, int noiseFloor)
{
    dataSet processingData (preProcesedData);

    for(int freqIndex = lowerBound_; freqIndex < upperBound_; freqIndex++)
    {
        processingData[freqIndex] = boost::make_shared<double>(checkAgainstNoiseFloor(*preProcesedData[freqIndex],noiseFloor));
    }

    return processingData;
}

std::bitset<8> SignalProcessingAlgorithm::evaluateBits(dataSet& processedData)
{
    auto bitLength = (upperBound_ - lowerBound_) / 8;
    auto currentBitIndex = (int) 0;
    std::bitset<8> outBits(0);

    for (int bitIndex = 0; bitIndex < 8; bitIndex++)
    {
        outBits[bitIndex] = false;

        for (int interIndex = 0; interIndex < bitLength; interIndex++)
        {
            currentBitIndex = lowerBound_ + (bitIndex * bitLength) + interIndex;

            if (*processedData[currentBitIndex] > 0)
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

std::string SignalProcessingAlgorithm::bigEndianConvert(std::bitset<8>& processedBits)
{
    auto outputString = (std::string)"";

    for (int bit_ = 0; bit_ < processedBits.size(); bit_++)
    {
        outputString.append( checkBit(processedBits[bit_]) );
    }

    return outputString;
}

std::string SignalProcessingAlgorithm::littleEndianConvert(std::bitset<8>& processedBits)
{
    auto outputString = (std::string)"";

    for (int bit_ = processedBits.size()-1; bit_ >= 0; bit_--)
    {
        outputString.append( checkBit( processedBits[bit_] ) );
    }

    return outputString;
}

// -- Hill Effect -- //
std::bitset<8> SPAHillEffect::evaluateBits(dataSet& processedData, const int bitLength)
{	
    double maxAmplitude = -1, maxIndex = -1;

    // Basic algorithm: Iterates through the bits, using a scalar value to interpolate
    // between frequencies (according to the boundaries set by owning FRP)
    for(int bit_ = lowerBound_; bit_ < upperBound_; bit_++)
    {
        double currentAmplitude = *processedData[bit_];

        if(currentAmplitude > maxAmplitude)
        {
            maxAmplitude = currentAmplitude;
            maxIndex = bit_;
        }
    }


    return std::bitset<8>(8);
}

// Need an intensity function!
std::string SPAIntensity::convertToBits(const double dataToConvert[], int noiseFloor)
{	
    return "IIIIIIII";
}