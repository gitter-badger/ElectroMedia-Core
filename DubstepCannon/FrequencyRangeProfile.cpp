#include "stdafx.h"
#include "FrequencyRangeProfile.h"

// FrequencyRangeProfile Constructor
// ---
// ...
FrequencyRangeProfile::FrequencyRangeProfile()
	: lowerBound_(0), upperBound_(0), bits_(8), name_("Untitled Range")
{ }

// FrequencyRangeProfile Destructor
// ---
// If we have stuff to dealloc, do it here
FrequencyRangeProfile::~FrequencyRangeProfile()
{ }

// format(double*,double*,enum int)
// ---
// Adjust a given frequency range according to the enumerated adjustmentType parameter.
// This function aims to guarantee that every bit's frequency width is equal to a power
// of BOUNDARY_CONVERSION_SCALAR (typically 10.91 Hz).
void FrequencyRangeProfile::format(double* lowerFrequency, double* upperFrequency, int adjustmentType)
{
	double spectralResolution_ = double(*upperFrequency - *lowerFrequency) / 8;
	double newResolution_ = double(ceil(spectralResolution_ / BOUNDARY_CONVERSION_SCALAR) * BOUNDARY_CONVERSION_SCALAR);
	int center_ = 0;

	switch(adjustmentType)
	{
	// In this case, we change the lower bound UNLESS we go below 0 Hz, whereupon we set the 
	// lower bound equal to 0 and change the upper bound appropriately
	case(ADJUSTMENT_TYPE_CHANGE_LOWER):
		*lowerFrequency = *upperFrequency - int(newResolution_ * 8);
		if(*lowerFrequency < BOUNDARY_CONVERSION_OFFSET)
		{
			*lowerFrequency = BOUNDARY_CONVERSION_OFFSET;
			*upperFrequency = int(newResolution_ * 8) + BOUNDARY_CONVERSION_OFFSET;
		}
		return;

	// In the centering case, we set the lower and upper bounds to 4 spectral bit widths from
	// the calculated center UNLESS we go below 0 Hz, whereupon we follow the same protocol as
	// in ADJUSTMENT_TYPE_CHANGE_LOWER
	case(ADJUSTMENT_TYPE_CENTER):
		center_ = int(*upperFrequency + *lowerFrequency) / 2;
		*lowerFrequency = center_ - int(newResolution_ * 4);
		if(*lowerFrequency < BOUNDARY_CONVERSION_OFFSET)
		{
			*lowerFrequency = BOUNDARY_CONVERSION_OFFSET;
			*upperFrequency = int(newResolution_ * 8) + BOUNDARY_CONVERSION_OFFSET;
		}
		else *upperFrequency = center_ + int(newResolution_ * 4);
		return;

	// All other cases we deem to be equal to ADJUSTMENT_TYPE_CHANGE_UPPER
	default:
		*upperFrequency = *lowerFrequency + int(newResolution_ * 8);
	}
}

// setIndexBounds(int, int, enum int)
// ---
// Adjusts the private lowerBound_ and upperbound_ variables using suggestions in the form of
// the first two parameters. The third parameter functions the same as in format(d,d,ei)
void FrequencyRangeProfile::setIndexBounds(int lowerIndex, int upperIndex, int adjustmentType)
{
	double lowerFrequency = convertIntToFrequency(lowerIndex);
	double upperFrequency = convertIntToFrequency(upperIndex);

	format(&lowerFrequency, &upperFrequency,adjustmentType);

	lowerBound_ = convertFrequencyToInt(lowerFrequency);
	upperBound_ = convertFrequencyToInt(upperFrequency);
}

// setIndexBounds(double, double, enum int)
// ---
// Functionally identical to setIndexBounds, except takes frequency inputs instead of indices
void FrequencyRangeProfile::setFrequencyBounds(double lowerFrequency, double upperFrequency, int adjustmentType)
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
// of the Arduino device selected in the active ArduinoReadableFile writer, and then turns
// specific bits on according to an algorithm.
//
// TODO:
// Uses an algorithm specified by an enumerated int to determine which bits should be on.
std::string FrequencyRangeProfile::convertToBits(double* dataToConvert, int noiseFloor)
{
	std::string outputString = "";
	int bitLength = (upperBound_ - lowerBound_) / bits_;
	bool wasAbove;

	for(int bit_ = 0; bit_ < bits_; bit_++)
	{
		wasAbove = false;
		for(int step = 0; !wasAbove && step < bitLength; step ++)
		{
			if(dataToConvert[lowerBound_ + bitLength * bit_ + step] > noiseFloor) 
			{
				wasAbove = true; 
			}
		}
	
		if(wasAbove) 
		{
			outputString.append("1");
		}
		else outputString.append("0");
	}

	return outputString;
}

// --

std::string IntensityFRP::convertToBits(double* dataToConvert, int noiseFloor)
{
	std::string outputString = "";
	int bitLength = (upperBound_ - lowerBound_) / bits_;
	bool wasAbove;

	for(int bit_ = 0; bit_ < bits_; bit_++)
	{
		/*wasAbove = false;
		for(int step = 0; !wasAbove && step < bitLength; step ++)
		{
			if(dataToConvert[lowerBound_ + bitLength * bit_ + step] > noiseFloor) 
			{
				wasAbove = true; 
			}
		}
	
		if(wasAbove) 
		{
			outputString.append("1");
		}
		else */outputString.append("1");
	}

	return outputString;
}
