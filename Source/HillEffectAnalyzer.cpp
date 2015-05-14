#include "stdafx.h"
#include "HillEffectAnalyzer.h"

HillEffectAnalyzer::HillEffectAnalyzer(int lowerBound, int upperBound, int resolution)
	: Analyzer(lowerBound, upperBound, resolution)
{

}

dynamic_bitset<> HillEffectAnalyzer::EvaluateBits(UniqueDataSet& processedData, const int bitLength)
{
	double maxAmplitude = -1, maxIndex = -1;

	// Basic algorithm: Iterates through the bits, using a scalar value to interpolate
	// between frequencies (according to the boundaries set by owning FRP)
	for (int bit_ = lowerBound_; bit_ < upperBound_; bit_++)
	{
		double currentAmplitude = processedData->at(bit_);

		if (currentAmplitude > maxAmplitude)
		{
			maxAmplitude = currentAmplitude;
			maxIndex = bit_;
		}
	}

	return dynamic_bitset<>(0);
}