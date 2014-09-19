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

// Operator = Overload
// ---
// When we use the assignment operator with an SPA, it is likely to not have
// the same algorithm tied to it. This forces the SPA to keep the same
// algorithm as before assignment, but changes its bits and frequency
// bounds to that of the assigner.
SignalProcessingAlgorithm& SignalProcessingAlgorithm::operator=(const SignalProcessingAlgorithm& other)
{
	if(this != &other)
	{
		this->bits_ = (int)&other.bits_;
		this->lowerBound_ = (int)&other.lowerBound_;
		this->upperBound_ = (int)&other.upperBound_;
	}
	return *this;
}

// setbounds(int,int)
// ---
// Redeclares the lower and upper bounds as dictated by the FrequencyRangeProfile
void SignalProcessingAlgorithm::setBounds(int lower, int upper)
{
	lowerBound_ = lower;
	upperBound_ = upper;
}

std::string SignalProcessingAlgorithm::convertToBits(double* dataToConvert, int noiseFloor) 
{	
	return "bbbbbbbb";
	/*std::string outputString = "";
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

	return outputString;*/
}

std::string SPAHillEffect::convertToBits(double* dataToConvert, int noiseFloor)
{	
	return "hhhhhhhh";
}

std::string SPAIntensity::convertToBits(double* dataToConvert, int noiseFloor)
{	
	return "iiiiiiii";
}