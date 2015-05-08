#include "stdafx.h"
#include "Analyzer.h"

#ifndef IntensityAnalyzerDefinition
#define IntensityAnalyzerDefinition

class IntensityAnalyzer : public Analyzer
{
public:
	std::string convertToBits(const double dataToConvert[], int noiseFloor);
};

#endif