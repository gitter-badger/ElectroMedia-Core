#include "stdafx.h"
#include "FeatureExtractionAnalyzer.h"

std::string FeatureExtractionAnalyzer::ConvertToBits(UniqueDataSet& processedData, const int bitLength)
{
	double valuesOfNotes[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int thisNoteType = 0;
	double thisNoteAmplitude = 0;

	for (int freqIndex = 0; freqIndex < upperBound_; freqIndex++)
	{
		thisNoteAmplitude = processedData->at(freqIndex);
		thisNoteType = ToNote(CoreMath::ConvertIntToFrequency(freqIndex));
		if (thisNoteType == NoteName::NONE)
		{
			continue;
		}
		valuesOfNotes[thisNoteType] += thisNoteAmplitude;
	}

	std::ostringstream buffer;
	buffer << valuesOfNotes[0];

	for (int noteIndex = 1; noteIndex < 12; noteIndex++)
	{
		buffer << ", " << valuesOfNotes[noteIndex];
	}

	return buffer.str();
}

NoteName FeatureExtractionAnalyzer::ToNote(double frequency)
{
	if (frequency < 30 || frequency > 2000 || isnan(frequency))
	{
		return NoteName::NONE;
	}

	double evalFrequency = frequency;
	while (evalFrequency < 440)
	{
		evalFrequency *= 2;
	}
	while (evalFrequency > 880)
	{
		evalFrequency /= 2;
	}

	// GROSS but it works for now
	if (evalFrequency < 466.16)
	{
		return NoteName::A;
	}
	if (evalFrequency < 466.16)
	{
		return NoteName::Asharp;
	}
	if (evalFrequency < 493.88)
	{
		return NoteName::B;
	}
	if (evalFrequency < 523.25)
	{
		return NoteName::C;
	}
	if (evalFrequency < 554.37)
	{
		return NoteName::Csharp;
	}
	if (evalFrequency < 587.33)
	{
		return NoteName::D;
	}
	if (evalFrequency < 622.25)
	{
		return NoteName::Dsharp;
	}
	if (evalFrequency < 659.25)
	{
		return NoteName::E;
	}
	if (evalFrequency < 698.46)
	{
		return NoteName::F;
	}
	if (evalFrequency < 739.99)
	{
		return NoteName::Fsharp;
	}
	if (evalFrequency < 783.99)
	{
		return NoteName::G;
	}
	/*	if (evalFrequency < 830.61)
	{*/
	return NoteName::Gsharp;
	//}
}