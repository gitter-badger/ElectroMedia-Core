#include "stdafx.h"
#include "Analyzer.h"
#include "NoteNames.h"

class FeatureExtractionAnalyzer : public Analyzer
{
public:
	std::string convertToBits(UniqueDataSet& dataToConvert, int noiseFloor);

private:
	NoteName toNote(double frequency);
};