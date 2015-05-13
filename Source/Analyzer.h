#include "stdafx.h"
#include <sstream>
#include "CoreMath.h"

#ifndef AnalyzerDefinition
#define AnalyzerDefinition

class Analyzer
{
public:
    // Constructors and Destructors
	Analyzer();
	Analyzer(int lowerBound, int upperBound);
	Analyzer(int lowerBound, int upperBound, int resolution);
	Analyzer(double lowerFrequency, double upperFrequency);
	Analyzer(double lowerFrequency, double upperFrequency, int resolution);
	~Analyzer();

    // Define lower and upper bounds (as indices) for this processor
    void SetBounds(const int lower, const int upper);

    // Heart and soul of the Signal Processing Algorithm. 
    virtual std::string ConvertToBits(UniqueDataSet& dataToConvert, int noiseFloor);

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
    virtual void PreProcessForConversion(UniqueDataSet& dataToConvert);
    virtual void ApplyNoiseFloor(UniqueDataSet& preProcesedData, int noiseFloor);
    virtual dynamic_bitset<> EvaluateBits(UniqueDataSet& processedData);
    virtual std::string BigEndianConvert(dynamic_bitset<>& processedBits);
    virtual std::string LittleEndianConvert(dynamic_bitset<>& processedBits);

    // These are used within the convertToBits methods
    int lowerBound_, upperBound_, bitResolution_;

private:
    std::string CheckBit(bool bitToCheck);
};

#endif