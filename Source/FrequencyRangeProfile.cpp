#include "stdafx.h"
#include "Constants.h"
#include "FrequencyRangeProfile.h"

// Empty FrequencyRangeProfile Constructor 
// ---
// ...
FrequencyRangeProfile::FrequencyRangeProfile()
    : lowerBound_(0), upperBound_(0), bits_(8), name_("Untitled Range")
{ }

// FrequencyRangeProfile Constructor with Analyzer param
// ---
// ...
FrequencyRangeProfile::FrequencyRangeProfile(Analyzer processor)
    : lowerBound_(0), upperBound_(0), bits_(8), name_("Untitled Range"), processor_(&processor)
{ }

// FrequencyRangeProfile Destructor
// ---
// If we have stuff to dealloc, do it here
FrequencyRangeProfile::~FrequencyRangeProfile()
{
    delete processor_;
}

// setProcessor(Analyzer)
// ---
// Set or redefine the algorithm that this FRP is using
void FrequencyRangeProfile::setProcessor(Analyzer& processor)
{
    this->processor_ = &processor;
    processor.setBounds(lowerBound_,upperBound_);
}

// format(double*,double*,enum int)
// ---
// Adjust a given frequency range according to the enumerated adjustmentType parameter.
// This function aims to guarantee that every bit's frequency width is equal to a power
// of BOUNDARY_CONVERSION_SCALAR (typically 10.91 Hz).
void FrequencyRangeProfile::format(double* lowerFrequency, double* upperFrequency, int adjustmentType)
{
    double spectralResolution_ = double(*upperFrequency - *lowerFrequency) / bits_;
    double newResolution_ = double(ceil(spectralResolution_ / BOUNDARY_CONVERSION_SCALAR) * BOUNDARY_CONVERSION_SCALAR);
	auto centeredFrequencies = new double[2];

    switch(adjustmentType)
    {
        // In this case, we change the lower bound UNLESS we go below 0 Hz, whereupon we set the 
        // lower bound equal to 0 and change the upper bound appropriately
    case(ADJUSTMENT_TYPE_CHANGE_LOWER):
        *lowerFrequency = formatChangeLower(*upperFrequency,newResolution_);
        return;

        // In the centering case, we set the lower and upper bounds to 4 spectral bit widths from
        // the calculated center UNLESS we go below 0 Hz, whereupon we follow the same protocol as
        // in ADJUSTMENT_TYPE_CHANGE_LOWER
    case(ADJUSTMENT_TYPE_CENTER):
        centeredFrequencies = formatCenter(*lowerFrequency,*upperFrequency,newResolution_);
        *lowerFrequency = centeredFrequencies[0];
        *upperFrequency = centeredFrequencies[1];
        return;

        // All other cases we deem to be equal to ADJUSTMENT_TYPE_CHANGE_UPPER
    default:
        *upperFrequency = formatChangeUpper(*lowerFrequency, newResolution_);
    }
}

double* FrequencyRangeProfile::formatCenter(double lowerFrequency, double upperFrequency, double resolution)
{
    double newFrequencies[] = {lowerFrequency, upperFrequency};
    int center_ = int(newFrequencies[0] + newFrequencies[1]) / 2;

    newFrequencies[0] = center_ - int(resolution * bits_/2);
    if(newFrequencies[0] < BOUNDARY_CONVERSION_OFFSET)
    {
        newFrequencies[0] = BOUNDARY_CONVERSION_OFFSET;
        newFrequencies[1] = int(resolution* bits_) + BOUNDARY_CONVERSION_OFFSET;
    }
    else newFrequencies[1] = center_ + int(resolution * bits_/2);

    return newFrequencies;
}

double FrequencyRangeProfile::formatChangeUpper(double lowerFrequency, double resolution)
{
    return lowerFrequency + int(resolution * bits_);
}

double FrequencyRangeProfile::formatChangeLower(double upperFrequency, double resolution)
{
    double newLowerFrequency = upperFrequency - int(resolution * bits_);
    if(newLowerFrequency < BOUNDARY_CONVERSION_OFFSET)
    {
        newLowerFrequency = BOUNDARY_CONVERSION_OFFSET;
        upperFrequency = int(resolution * bits_) + BOUNDARY_CONVERSION_OFFSET;
    }
    return newLowerFrequency;
}

// setIndexBounds(int, int, enum int)
// ---
// Adjusts the private lowerBound_ and upperbound_ variables using suggestions in the form of
// the first two parameters. The third parameter functions the same as in format(d,d,ei)
void FrequencyRangeProfile::setIndexBounds(int lowerIndex, int upperIndex, int adjustmentType)
{
    initializeFrequencyBounds(convertIntToFrequency(lowerIndex),convertIntToFrequency(upperIndex),adjustmentType);

    // Tell the processor that we updated our bounds
    processor_->setBounds(lowerBound_,upperBound_);
}

// setIndexBounds(double, double, enum int)
// ---
// Functionally identical to setIndexBounds, except takes frequency inputs instead of indices
void FrequencyRangeProfile::setFrequencyBounds(double lowerFrequency, double upperFrequency, int adjustmentType)
{
    initializeFrequencyBounds(lowerFrequency,upperFrequency,adjustmentType);

    // Tell the processor that we updated our bounds
    processor_->setBounds(lowerBound_,upperBound_);
}

// setIndexBounds(double, double, enum int)
// ---
// IMPORTANT! This is CRITICALLY different from setFrequencyBounds and setIndexBounds in the
// fact that this does NOT attempt to interface with the processor. At the point of time when
// this method is called processor should NOT be initialized and the other two functions are 
// likely to lead to nullptrs. Use this if you are not interfacing with the processor.
void FrequencyRangeProfile::initializeFrequencyBounds(double lowerFrequency, double upperFrequency, int adjustmentType)
{
    format(&lowerFrequency, &upperFrequency, adjustmentType);

    lowerBound_ = convertFrequencyToInt(lowerFrequency);
    upperBound_ = convertFrequencyToInt(upperFrequency);
}

// std::string = convertToBits(double*, int)
// ---
// [+ Work in Progress +]
//
// Creates an array of bits of length <bits_> which correspond to specific output pins
// of the Arduino device selected in the active ArduinoReadableFileWriter writer, and then turns
// specific bits on according to an algorithm.
//
// TODO:
// Uses an algorithm specified by an enumerated int to determine which bits should be on.
std::string FrequencyRangeProfile::convertToBits(UniqueDataSet& dataToConvert, int noiseFloor)
{
    return processor_->convertToBits(dataToConvert,noiseFloor);;
}
