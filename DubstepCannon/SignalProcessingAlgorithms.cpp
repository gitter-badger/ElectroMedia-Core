#include "stdafx.h"
#include "SignalProcessingAlgorithms.h"

// SignalProcessingAlgorithm Constructor
// ---
// ...
SignalProcessingAlgorithm::SignalProcessingAlgorithm()
	: lowerBound_(0), upperBound_(0), bits_(8)
{ }

// SignalProcessingAlgorithm Destructor
// ---
// If we have stuff to dealloc, do it here
SignalProcessingAlgorithm::~SignalProcessingAlgorithm()
{ }

// setbounds(int,int)
// ---
// Redeclares the lower and upper bounds as dictated by the FrequencyRangeProfile
void SignalProcessingAlgorithm::setBounds(const int lower, const int upper)
{
	lowerBound_ = (int)lower;
	this->upperBound_ = upper;
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
	std::string outputString = "";
	int bitLength = (upperBound_ - lowerBound_) / bits_;
	bool wasAbove;

	// By default, this result is Big Endian due to the nature of frequencies increasing 
	// left-to-right. The nature of the output can be altered by changing the 
	// OUTPUT_IS_BIG_ENDIAN setting in "stdafx.h" which will then reverse the output.
	if(OUTPUT_IS_BIG_ENDIAN)
	{
		// Basic algorithm: Iterates through the bits, using a scalar value to interpolate
		// between frequencies (according to the boundaries set by owning FRP_
		for(int bit_ = 0; bit_ < bits_; bit_++)
		{
			wasAbove = false;
			for(int step = 0; step < bitLength; step ++)
			{
				if(dataToConvert[lowerBound_ + bitLength * bit_ + step] > noiseFloor) 
				{
					wasAbove = true;
					break;
				}
			}
	
			if(wasAbove) 
			{
				outputString.append("1");
			}
			else outputString.append("0");
		}
	}
	else
	{
		// Basic algorithm: Iterates through the bits, using a scalar value to interpolate
		// between frequencies (according to the boundaries set by owning FRP_
		for(int bit_ = bits_; bit_ >= 0; bit_--)
		{
			wasAbove = false;
			for(int step = 0; step < bitLength; step ++)
			{
				if(dataToConvert[lowerBound_ + bitLength * bit_ + step] > noiseFloor) 
				{
					wasAbove = true;
					break;
				}
			}
	
			if(wasAbove) 
			{
				outputString.append("1");
			}
			else outputString.append("0");
		}
	}


	return outputString;
}

// HILL EFFECT
// convertToBits(double*, int)
// ---
// Attempts to find any frequency amplitude above the noise floor, and then sets all bits high
// if they are lower than the maximum significant frequency within bounds.
// 
// Result is by default Big Endian, but this can be changed through config by
// setting OUTPUT_IS_BIG_ENDIAN to false in "stdafx.h"
std::string SPAHillEffect::convertToBits(const double* dataToConvert, int noiseFloor)
{	
	std::string outputString = "";
	int bitLength = (upperBound_ - lowerBound_) / bits_;
	
	double maxAmplitude = noiseFloor, maxIndex = -1;

	// Basic algorithm: Iterates through the bits, using a scalar value to interpolate
	// between frequencies (according to the boundaries set by owning FRP)
	for(int bit_ = 0; bit_ < bits_; bit_++)
	{
		for(int step = 0; step < bitLength; step ++)
		{
			double currentAmplitude = dataToConvert[lowerBound_ + bitLength * bit_ + step];
			if(currentAmplitude > maxAmplitude)
			{
				maxAmplitude = currentAmplitude;
				maxIndex = bit_; // Does this continually point to bit_? Or is it set to the value?
			}
		}
	}

	// By default, this result is Big Endian due to the nature of frequencies increasing 
	// left-to-right. The nature of the output can be altered by changing the 
	// OUTPUT_IS_BIG_ENDIAN setting in "stdafx.h" which will then reverse the output.
	if(OUTPUT_IS_BIG_ENDIAN)
	{
		// Should find a cleaner way to do this
		for(int bit_ = 0; bit_ < bits_; bit_++)
		{
			if(bit_ <= maxIndex)
			{
				outputString.append("1");
			}
			else outputString.append("0");
		}
	}
	else // ! OUTPUT_IS_BIG_ENDIAN
	{
		for(int bit_ = bits_; bit_ >= 0; bit_--)
		{
			if(bit_ <= maxIndex)
			{
				outputString.append("1");
			}
			else outputString.append("0");
		}
	}

	return outputString;
}

std::string SPAIntensity::convertToBits(const double* dataToConvert, int noiseFloor)
{	
	return "IIIIIIII";
}