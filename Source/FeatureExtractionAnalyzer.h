#include "stdafx.h"
#include "Analyzer.h"
#include "CoreMath.h"
#include "NoteNames.h"

class FeatureExtractionAnalyzer : public Analyzer
{
public:
	std::string ConvertToBits(UniqueDataSet& dataToConvert, int noiseFloor);

private:
	NoteName ToNote(double frequency);
};