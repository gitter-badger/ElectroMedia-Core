#include "stdafx.h"
#include "Analyzer.h"
#include "CoreMath.h"
#include "NoteNames.h"

#ifndef EMC_FeatureExtractionAnalyzer_H_
#define EMC_FeatureExtractionAnalyzer_H_

class FeatureExtractionAnalyzer : public Analyzer
{
public:
	FeatureExtractionAnalyzer(int lower_bound, int upper_bound, int resolution);
	std::string ConvertToBits(UniqueDataSet& processed_data, int noise_floor);

private:
	NoteName ToNote(double frequency);
};

#endif