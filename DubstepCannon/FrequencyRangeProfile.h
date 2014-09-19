#include "stdafx.h"
#include "SignalProcessingAlgorithms.h"

class FrequencyRangeProfile
{
public:
	FrequencyRangeProfile();
	FrequencyRangeProfile(SignalProcessingAlgorithm processor);
	~FrequencyRangeProfile();
	
	void setProcessor(SignalProcessingAlgorithm processor);
	void setIndexBounds(int lower, int upper, int adjustmentType);
	void setFrequencyBounds(double lowerFrequency, double upperFrequency, int adjustmentType);
	std::string convertToBits(double* dataToConvert, int noiseFloor);

protected:
	int lowerBound_, upperBound_, bits_;

private:
	SignalProcessingAlgorithm* processor_;
	std::string name_;
	void format(double* lowerFrequency, double* upperFrequency, int adjustmentType);
};