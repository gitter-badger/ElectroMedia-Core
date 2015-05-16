#include "stdafx.h"
#include "HillEffectAnalyzer.h"

HillEffectAnalyzer::HillEffectAnalyzer(int lower_bound, int upper_bound, int resolution)
	: Analyzer(lower_bound, upper_bound, resolution)
{

}

dynamic_bitset<> HillEffectAnalyzer::EvaluateBits(UniqueDataSet& processedData, const int bitLength)
{
	double max_amplitude = -1, max_index = -1;

	// Basic algorithm: Iterates through the bits, using a scalar value to interpolate
	// between frequencies (according to the boundaries set by owning FRP)
	for (int bit_ = lower_bound_; bit_ < upper_bound_; bit_++)
	{
		double current_amplitude = processedData->at(bit_);

		if (current_amplitude > max_amplitude)
		{
			max_amplitude = current_amplitude;
			max_index = bit_;
		}
	}

	return dynamic_bitset<>(0);
}