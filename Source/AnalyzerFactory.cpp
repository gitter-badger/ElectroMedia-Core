#include "stdafx.h"
#include "AnalyzerFactory.h"

Analyzer* AnalyzerFactory::Create(std::string type, int lowerBound, int upperBound, int resolution)
{
	Validate(lowerBound, upperBound, resolution);

	if (type.compare("Analyzer") == 0)
	{
		return new Analyzer(lowerBound, upperBound, resolution);
	}

	if (type.compare("HillEffect") == 0)
	{
		return new HillEffectAnalyzer(lowerBound, upperBound, resolution);
	}

	if (type.compare("Intensity") == 0)
	{
		return new IntensityAnalyzer(lowerBound, upperBound, resolution);
	}

	if (type.compare("FeatureExtraction") == 0)
	{
		return new FeatureExtractionAnalyzer(lowerBound, upperBound, resolution);
	}

	return new Analyzer();
}

// Indices
Analyzer* AnalyzerFactory::Create(std::string type)
{
	return Create(type, 0, 0, 1);
}

Analyzer* AnalyzerFactory::Create(std::string type, int lowerBound, int upperBound)
{
	return Create(type, lowerBound, upperBound, 1);
}

// Frequencies
Analyzer* AnalyzerFactory::Create(std::string type, double lowerFrequency, double upperFrequency)
{
	return Create(type, lowerFrequency, upperFrequency, 1);
}

Analyzer* AnalyzerFactory::Create(std::string type, double lowerFrequency, double upperFrequency, int resolution)
{
	auto lowerBound = CoreMath::ConvertFrequencyToInt(lowerFrequency);
	auto upperBound = CoreMath::ConvertFrequencyToInt(upperFrequency);

	return Create(type, lowerBound, upperBound, resolution);
}

void AnalyzerFactory::Validate(int& lowerBound, int& upperBound, int& resolution)
{
	// Analyzer has an absolute minimum index of 0
	lowerBound = std::max(0, lowerBound);

	// Analyzer must have a band of at least one bit
	upperBound = std::min(lowerBound + 1, upperBound);

	// Resolution is not unreasonable (e.g. at least 1 and no more than the width of indices
	auto maximumResolution = upperBound - lowerBound;
	resolution = std::max(1, resolution);
	resolution = std::min(resolution, maximumResolution);
}