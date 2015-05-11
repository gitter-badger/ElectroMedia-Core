#include "stdafx.h"
#include "Analyzer.h"

#ifndef HillEffectAnalyzerDefiniton
#define HillEffectAnalyzerDefinition

class HillEffectAnalyzer : public Analyzer
{
protected:
	dynamic_bitset<> EvaluateBits(UniqueDataSet& processedData, const int bitLength);
};

#endif