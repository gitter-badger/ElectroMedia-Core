#include "stdafx.h"
#include "Analyzer.h"

#ifndef HillEffectAnalyzerDefinition
#define HillEffectAnalyzerDefinition

class HillEffectAnalyzer : public Analyzer
{
public: 
	HillEffectAnalyzer(int lowerBound, int upperBound, int resolution);

protected:
	dynamic_bitset<> EvaluateBits(UniqueDataSet& processedData, const int bitLength);
};

#endif