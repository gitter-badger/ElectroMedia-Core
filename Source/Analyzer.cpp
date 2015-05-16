#include "stdafx.h"
#include "Constants.h"
#include "Analyzer.h"

// Analyzer Constructor
// ---
// ...
Analyzer::Analyzer()
	: Analyzer(0,0,1)
{ }

Analyzer::Analyzer(int lower_bound, int upper_bound)
	: Analyzer(lower_bound, upper_bound, 1)
{ }

Analyzer::Analyzer(int lower_bound, int upper_bound, int resolution)
	: lower_bound_(lower_bound),
	  upper_bound_(upper_bound),
	  bit_resolution_(resolution)
{ }

Analyzer::Analyzer(double lower_frequency, double upper_frequency)
	: Analyzer(lower_frequency, upper_frequency, 1)
{
}

Analyzer::Analyzer(double lower_frequency, double upper_frequency, int resolution)
	: bit_resolution_(resolution)
{
	lower_bound_ = CoreMath::ConvertFrequencyToInt(lower_frequency);
	upper_bound_ = CoreMath::ConvertFrequencyToInt(upper_frequency);
}

Analyzer::~Analyzer() { }


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
std::string Analyzer::ConvertToBits(UniqueDataSet& data_to_convert, int noise_floor)
{
	PreProcessForConversion(data_to_convert);
	ApplyNoiseFloor(data_to_convert, noise_floor);
	auto resulting_bits = EvaluateBits(data_to_convert);

    // By default, this result is Big Endian due to the nature of frequencies increasing 
    // left-to-right. The nature of the output can be altered by changing the 
    // OUTPUT_IS_BIG_ENDIAN setting in "stdafx.h" which will then reverse the output.
    if(OUTPUT_IS_BIG_ENDIAN)
    {
		return BigEndianConvert(resulting_bits);
    }
	return LittleEndianConvert(resulting_bits);
}

void Analyzer::PreProcessForConversion(UniqueDataSet& data_to_convert)
{
    // Nothing should really happen 
}

double checkAgainstNoiseFloor(double frequency, int noise_floor)
{
	if (frequency < noise_floor)
    {
        return 0;
    }

    return frequency;
}

void Analyzer::ApplyNoiseFloor(UniqueDataSet& preprocessed_data, int noise_floor)
{
    // Replace with iterator
	DataSetIterator it = preprocessed_data->begin();
	while (it != preprocessed_data->end())
    {
		*it = checkAgainstNoiseFloor(*it, noise_floor);
        ++it;
    }
}

dynamic_bitset<> Analyzer::EvaluateBits(UniqueDataSet& processed_data)
{
	auto bit_length = (int)floor(upper_bound_ - lower_bound_) / bit_resolution_;
    auto current_bit = (int) 0;
	dynamic_bitset<> out_bits(bit_length);

	for (int bitIndex = 0; bitIndex < bit_length; ++bitIndex)
    {
		out_bits[bitIndex] = false;
		for (int interIndex = 0; interIndex < bit_resolution_; interIndex++)
        {
			current_bit = lower_bound_ + (bitIndex * bit_resolution_) + interIndex;
			if (processed_data->at(current_bit) > 0)
            {
				out_bits[bitIndex] = true;
                break;
            }
        }
    }

	return out_bits;
}


std::string Analyzer::CheckBit(bool bit_to_check)
{
	if (bit_to_check)
    {
        return "1";
    }

    return "0";
}

std::string Analyzer::BigEndianConvert(dynamic_bitset<>& processed_bits)
{
	auto output_string = (std::string)"";

	for (int bit = 0; bit < processed_bits.size(); bit++)
    {
		output_string.append(CheckBit(processed_bits[bit]));
    }

	return output_string;
}

std::string Analyzer::LittleEndianConvert(dynamic_bitset<>& processed_bits)
{
    auto output_string = (std::string)"";

	for (int bit = processed_bits.size() - 1; bit >= 0; bit--)
    {
		output_string.append(CheckBit(processed_bits[bit]));
    }

	return output_string;
}