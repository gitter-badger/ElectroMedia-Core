#include "stdafx.h"
#include "Analyzer.h"
#include "CoreMath.h"
#include "NoteNames.h"

#ifndef FeatureExtractionAnalyzerDefinition
#define FeatureExtractionAnalyzerDefinition

class FeatureExtractionAnalyzer : public Analyzer
{
public:
	std::string ConvertToBits(UniqueDataSet& dataToConvert, int noiseFloor);

private:
	NoteName ToNote(double frequency);
};

#endif