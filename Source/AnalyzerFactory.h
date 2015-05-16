#include "stdafx.h"
#include "Analyzer.h"
#include "HillEffectAnalyzer.h"
#include "FeatureExtractionAnalyzer.h"
#include "IntensityAnalyzer.h"

#ifndef EMC_AnalyzerFactory_H_
#define EMC_AnalyzerFactory_H_

class AnalyzerFactory
{
public:
	Analyzer* Create(std::string type);
	Analyzer* Create(std::string type, int lowerBound, int upperBound);
	Analyzer* Create(std::string type, int lowerBound, int upperBound, int resolution);
	Analyzer* Create(std::string type, double lowerFrequency, double upperFrequency);
	Analyzer* Create(std::string type, double lowerFrequency, double upperFrequency, int resolution);

private: 
	void Validate(int& lowerBound, int& upperBound, int& resolution);
};

#endif