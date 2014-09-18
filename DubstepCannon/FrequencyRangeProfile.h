#include "stdafx.h"

class FrequencyRangeProfile
{
public:
	FrequencyRangeProfile();
	~FrequencyRangeProfile();
	
	void setIndexBounds(int lower, int upper, int adjustmentType);
	void setFrequencyBounds(double lowerFrequency, double upperFrequency, int adjustmentType);
	std::string convertToBits(double* dataToConvert, int noiseFloor);

protected:
	int lowerBound_, upperBound_, bits_;

private:
	std::string name_;
	void format(double* lowerFrequency, double* upperFrequency, int adjustmentType);
};

// Subclasses
class IntensityFRP : FrequencyRangeProfile
{
public:
	std::string convertToBits(double* dataToConvert, int noiseFloor);
};