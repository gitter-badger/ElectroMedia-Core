#include "stdafx.h"
#include <sstream>
#include "CoreMath.h"
#include "ConfigurationFileFields.h"

#ifndef EMC_Analyzer_H_
#define EMC_Analyzer_H_

class Analyzer
{
public:
    // Constructors and Destructors
	Analyzer();
	Analyzer(int lower_bound, int upper_bound);
	Analyzer(int lower_bound, int upper_bound, int resolution);
	Analyzer(double lower_frequency, double upper_frequency);
	Analyzer(double lower_frequency, double upper_frequency, int resolution);
	~Analyzer();

    // Define lower and upper bounds (as indices) for this processor
    void SetBounds(const int lower, const int upper);

	virtual void Analyze(vector<double> spectral_data);

    // Heart and soul of the Signal Processing Algorithm. 
    virtual std::string ConvertToBits(UniqueDataSet& data_to_convert, int noiseFloor);

protected:
    // The following are part of convertToBits, which should only be modified in extreme
    // cases. The program flow is as follows
    // 1. preProcessForConversion -- does any necessary preProcessing to the data
    // 2. evaluateNoiseFloor -- scrapes out any values below noise floor
    // 3. evaluateBits -- determines which bits are high or low and generates a bool[].
    //	  - NOTE: The program flow ends here and returns the bool[] if the ARFWriter 
    //		is not in TEXT mode.
    // 4. ___EndianConvert -- Called according to endianness as indicated in the config
    //		file, this converts a bool[] into a string
	virtual void PreProcessForConversion(UniqueDataSet& data_to_convert);
    virtual void ApplyNoiseFloor(UniqueDataSet& preprocessed_data, int noise_floor);
	virtual dynamic_bitset<> EvaluateBits(UniqueDataSet& processed_bits);
	virtual std::string BigEndianConvert(dynamic_bitset<>& processed_bits);
	virtual std::string LittleEndianConvert(dynamic_bitset<>& processed_bits);

    // These are used within the convertToBits methods
    int lower_bound_, upper_bound_, bit_resolution_;

private:
    std::string CheckBit(bool bitToCheck);
};

#endif