#include "stdafx.h"
#include "FeatureExtractionAnalyzer.h"

FeatureExtractionAnalyzer::FeatureExtractionAnalyzer(int lower_bound, int upper_bound, int resolution)
	: Analyzer(lower_bound, upper_bound, resolution)
{

}

std::string FeatureExtractionAnalyzer::ConvertToBits(UniqueDataSet& processed_data, const int noise_floor)
{
	double values_of_notes[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int note_type = 0;
	double note_amplitude = 0;

	for (int freqIndex = 0; freqIndex < upper_bound_; freqIndex++)
	{
		note_amplitude = processed_data->at(freqIndex);
		note_type = ToNote(CoreMath::ConvertIntToFrequency(freqIndex));
		if (note_type == NoteName::NONE)
		{
			continue;
		}
		values_of_notes[note_type] += note_amplitude;
	}

	std::ostringstream buffer;
	buffer << values_of_notes[0];

	for (int note_index = 1; note_index < 12; note_index++)
	{
		buffer << ", " << values_of_notes[note_index];
	}

	return buffer.str();
}

NoteName FeatureExtractionAnalyzer::ToNote(double frequency)
{
	if (frequency < 30 || frequency > 2000 || isnan(frequency))
	{
		return NoteName::NONE;
	}

	double evaluated_frequency = frequency;
	while (evaluated_frequency < 440)
	{
		evaluated_frequency *= 2;
	}
	while (evaluated_frequency > 880)
	{
		evaluated_frequency /= 2;
	}

	// GROSS but it works for now
	if (evaluated_frequency < 466.16)
	{
		return NoteName::A;
	}
	if (evaluated_frequency < 466.16)
	{
		return NoteName::Asharp;
	}
	if (evaluated_frequency < 493.88)
	{
		return NoteName::B;
	}
	if (evaluated_frequency < 523.25)
	{
		return NoteName::C;
	}
	if (evaluated_frequency < 554.37)
	{
		return NoteName::Csharp;
	}
	if (evaluated_frequency < 587.33)
	{
		return NoteName::D;
	}
	if (evaluated_frequency < 622.25)
	{
		return NoteName::Dsharp;
	}
	if (evaluated_frequency < 659.25)
	{
		return NoteName::E;
	}
	if (evaluated_frequency < 698.46)
	{
		return NoteName::F;
	}
	if (evaluated_frequency < 739.99)
	{
		return NoteName::Fsharp;
	}
	if (evaluated_frequency < 783.99)
	{
		return NoteName::G;
	}
	/*	if (evaluated_frequency < 830.61)
	{*/
	return NoteName::Gsharp;
	//}
}