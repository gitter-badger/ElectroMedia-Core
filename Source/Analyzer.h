#include <sstream>
#include "stdafx.h"

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

class SPAToPCAExperiment : public Analyzer
{
public:
	std::string convertToBits(UniqueDataSet& dataToConvert, int noiseFloor);
	enum NoteName { A, Asharp, B, C, Csharp, D, Dsharp, E, F, Fsharp, G, Gsharp, NONE };

private:
	NoteName toNote(double frequency);
};

//=====================
// SUBCLASSES BELOW...
//=====================

// INTENSITY
// ---
// Watches Intensity of a specific frequency range; returns 1 bit
class SPAIntensity : public Analyzer
{
public:
    std::string convertToBits(const double dataToConvert[], int noiseFloor);
};

// WATCH FREQUENCY
// ---
// Watches only an exact frequency; returns the value in binary
class SPAWatchFrequency : public Analyzer
{
public:
    std::string convertToBits(const double dataToConvert[], int noiseFloor);
    void setWatchFrequency(double watchFrequency);

private:
    // The index of the frequency that this SPA should watch
    int watchBound_;
};

// PERCUSSION
// ---
// Watches for percussion and does specific things for them. I want this to be configurable.
// For instance, on HATS make all bits go to a value of 1, or etc.
class SPAPercussion : public Analyzer
{
public:
    std::string convertToBits(const double dataToConvert[], int noiseFloor);

private:
    // If setHighOnHat is true, the entire range goes high when the hat sounds
    bool setHighOnHat;
};

// HILL EFFECT
// ---
// Turns all bits lower than the maximum amplitude within a range to 1
// Useful for climbing frequency effects as in "Contact" by Daft Punk
class SPAHillEffect : public Analyzer
{
protected:
    dynamic_bitset<> evaluateBits(UniqueDataSet& processedData, const int bitLength);
};