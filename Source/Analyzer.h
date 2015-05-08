#include <sstream>
#include "stdafx.h"

#ifndef AnalyzerDefinition
#define AnalyzerDefinition

class Analyzer
{
public:
    // Constructors and Destructors
	Analyzer();
	Analyzer(int numberOfBits);
	~Analyzer();

    // Define lower and upper bounds (as indices) for this processor
    void setBounds(const int lower, const int upper);

    // Heart and soul of the Signal Processing Algorithm. 
    virtual std::string convertToBits(UniqueDataSet& dataToConvert, int noiseFloor);

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
    virtual void preProcessForConversion(UniqueDataSet& dataToConvert);
    virtual void applyNoiseFloor(UniqueDataSet& preProcesedData, int noiseFloor);
    virtual dynamic_bitset<> evaluateBits(UniqueDataSet& processedData);
    virtual std::string bigEndianConvert(dynamic_bitset<>& processedBits);
    virtual std::string littleEndianConvert(dynamic_bitset<>& processedBits);

    // These are used within the convertToBits methods
    int lowerBound_, upperBound_, bits_;

private:
    std::string checkBit(bool bitToCheck);
};

#endif