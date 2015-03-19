#include "stdafx.h"
#include "SignalProcessingAlgorithms.h"

// SignalProcessingAlgorithm Constructor
// ---
// ...
SignalProcessingAlgorithm::SignalProcessingAlgorithm()
    : lowerBound_(0), upperBound_(0), bits_(4)
{ /* - No op - */ }

SignalProcessingAlgorithm::SignalProcessingAlgorithm(int numberOfBits)
    : lowerBound_(0), upperBound_(0)
{
    bits_ = numberOfBits;
}

// SignalProcessingAlgorithm Destructor
// ---
// If we have stuff to dealloc, do it here
SignalProcessingAlgorithm::~SignalProcessingAlgorithm()
{ /* - No op - */ }

// setbounds(int,int)
// ---
// Redeclares the lower and upper bounds as dictated by the FrequencyRangeProfile
void SignalProcessingAlgorithm::setBounds(const int lower, const int upper)
{
    lowerBound_ = lower;
    upperBound_ = upper;
}

// BASE
// convertToBits(double*, int)
// ---
// Main variant of the processor.convertToBits(); function. This takes the array of
// data doubles and performs some algorithm (as defined by derived/child classes)
// to return a string/bytestream. In this main variety, the algorithm merely checks
// for signficant (above noise floor) frequencies, and marks the indices as high.
// 
// Result is by default Big Endian, but this can be changed through config by
// setting OUTPUT_IS_BIG_ENDIAN to false in "stdafx.h"
std::string SignalProcessingAlgorithm::convertToBits(UniqueDataSet& dataToConvert, int noiseFloor)
{
    preProcessForConversion(dataToConvert);
    applyNoiseFloor(dataToConvert, noiseFloor);
    auto resultingBits = evaluateBits(dataToConvert);

    // By default, this result is Big Endian due to the nature of frequencies increasing 
    // left-to-right. The nature of the output can be altered by changing the 
    // OUTPUT_IS_BIG_ENDIAN setting in "stdafx.h" which will then reverse the output.
    if(OUTPUT_IS_BIG_ENDIAN)
    {
        return bigEndianConvert(resultingBits);
    }
    return littleEndianConvert(resultingBits);
}

void SignalProcessingAlgorithm::preProcessForConversion(UniqueDataSet& dataToConvert)
{
    // Nothing should really happen 
}

double checkAgainstNoiseFloor(double frequency, int noiseFloor)
{
    if(frequency < noiseFloor)
    {
        return 0;
    }

    return frequency;
}

void SignalProcessingAlgorithm::applyNoiseFloor(UniqueDataSet& preProcesedData, int noiseFloor)
{
    // Replace with iterator
    DataSetIterator it = preProcesedData->begin();
    while (it != preProcesedData->end())
    {
        *it = checkAgainstNoiseFloor(*it, noiseFloor);
        ++it;
    }
}

dynamic_bitset<> SignalProcessingAlgorithm::evaluateBits(UniqueDataSet& processedData)
{
    auto bitLength = (upperBound_ - lowerBound_) / bits_;
    auto currentBitIndex = (int) 0;
    dynamic_bitset<> outBits(bits_);

    for (int bitIndex = 0; bitIndex < bits_; bitIndex++)
    {
        outBits[bitIndex] = false;
        for (int interIndex = 0; interIndex < bitLength; interIndex++)
        {
            currentBitIndex = lowerBound_ + (bitIndex * bitLength) + interIndex;
            if (processedData->at(currentBitIndex) > 0)
            {
                outBits[bitIndex] = true;
                break;
            }
        }
    }

    return outBits;
}


std::string SignalProcessingAlgorithm::checkBit(bool bitToCheck)
{
    if(bitToCheck)
    {
        return "1";
    }

    return "0";
}

std::string SignalProcessingAlgorithm::bigEndianConvert(dynamic_bitset<>& processedBits)
{
    auto outputString = (std::string)"";

    for (int bit_ = 0; bit_ < processedBits.size(); bit_++)
    {
        outputString.append( checkBit(processedBits[bit_]) );
    }

    return outputString;
}

std::string SignalProcessingAlgorithm::littleEndianConvert(dynamic_bitset<>& processedBits)
{
    auto outputString = (std::string)"";

    for (int bit_ = processedBits.size()-1; bit_ >= 0; bit_--)
    {
        outputString.append( checkBit( processedBits[bit_] ) );
    }

    return outputString;
}

std::string SPAToPCAExperiment::convertToBits(UniqueDataSet& processedData, const int bitLength)
{
	double valuesOfNotes[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int thisNoteType = 0;
	double thisNoteAmplitude = 0;

	for (int freqIndex = 0; freqIndex < upperBound_; freqIndex++)
	{
		thisNoteAmplitude = processedData->at(freqIndex);
		thisNoteType = toNote(convertIntToFrequency(freqIndex));
		if (thisNoteType == SPAToPCAExperiment::NONE)
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

SPAToPCAExperiment::NoteName SPAToPCAExperiment::toNote(double frequency)
{
	if (frequency < 30 || frequency > 2000 || isnan(frequency))
	{
		return SPAToPCAExperiment::NONE;
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
		return SPAToPCAExperiment::A;
	}
	if (evalFrequency < 466.16)
	{
		return SPAToPCAExperiment::Asharp;
	}
	if (evalFrequency < 493.88)
	{
		return SPAToPCAExperiment::B;
	}
	if (evalFrequency < 523.25)
	{
		return SPAToPCAExperiment::C;
	}
	if (evalFrequency < 554.37)
	{
		return SPAToPCAExperiment::Csharp;
	}
	if (evalFrequency < 587.33)
	{
		return SPAToPCAExperiment::D;
	}
	if (evalFrequency < 622.25)
	{
		return SPAToPCAExperiment::Dsharp;
	}
	if (evalFrequency < 659.25)
	{
		return SPAToPCAExperiment::E;
	}
	if (evalFrequency < 698.46)
	{
		return SPAToPCAExperiment::F;
	}
	if (evalFrequency < 739.99)
	{
		return SPAToPCAExperiment::Fsharp;
	}
	if (evalFrequency < 783.99)
	{
		return SPAToPCAExperiment::G;
	}
/*	if (evalFrequency < 830.61)
	{*/
		return SPAToPCAExperiment::Gsharp;
	//}
}



// -- Hill Effect -- //
dynamic_bitset<> SPAHillEffect::evaluateBits(UniqueDataSet& processedData, const int bitLength)
{	
    double maxAmplitude = -1, maxIndex = -1;

    // Basic algorithm: Iterates through the bits, using a scalar value to interpolate
    // between frequencies (according to the boundaries set by owning FRP)
    for(int bit_ = lowerBound_; bit_ < upperBound_; bit_++)
    {
        double currentAmplitude = processedData->at(bit_);

        if(currentAmplitude > maxAmplitude)
        {
            maxAmplitude = currentAmplitude;
            maxIndex = bit_;
        }
    }


    return dynamic_bitset<>(0);
}

// Need an intensity function!
std::string SPAIntensity::convertToBits(const double dataToConvert[], int noiseFloor)
{	
    return "IIIIIIII";
}