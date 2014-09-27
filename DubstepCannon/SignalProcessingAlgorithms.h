#include "stdafx.h"

class SignalProcessingAlgorithm
{
public:
	// Constructors and Destructors
	SignalProcessingAlgorithm();
	~SignalProcessingAlgorithm();
	
	// Define lower and upper bounds (as indices) for this processor
	void setBounds(const int lower, const int upper);
	
	// Heart and soul of the Signal Processing Algorithm
	virtual std::string convertToBits(const double* dataToConvert, int noiseFloor);
	
protected:
	// These are used within the convertToBits methods and thus must be protected
	int lowerBound_, upperBound_, bits_;

private:
	// Hidden function used exclusively by base class; checks to see if a specific
	// bit should be set to high
	bool checkBit(const double* dataToConvert, int bit, int noiseFloor);
};

//=====================
// SUBCLASSES BELOW...
//=====================

// INTENSITY
// ---
// Watches Intensity of a specific frequency range; returns 1 bit
class SPAIntensity : public SignalProcessingAlgorithm
{
public:
	std::string convertToBits(const double* dataToConvert, int noiseFloor);
};

// WATCH FREQUENCY
// ---
// Watches only an exact frequency; returns the value in binary
class SPAWatchFrequency : public SignalProcessingAlgorithm
{
public:
	std::string convertToBits(const double* dataToConvert, int noiseFloor);
	void setWatchFrequency(double watchFrequency);

private:
	// The index of the frequency that this SPA should watch
	int watchBound_;
};

// PERCUSSION
// ---
// Watches for percussion and does specific things for them. I want this to be configurable.
// For instance, on HATS make all bits go to a value of 1, or etc.
class SPAPercussion : public SignalProcessingAlgorithm
{
public:
	std::string convertToBits(const double* dataToConvert, int noiseFloor);

private:
	// If setHighOnHat is true, the entire range goes high when the hat sounds
	bool setHighOnHat;
};

// HILL EFFECT
// ---
// Turns all bits lower than the maximum amplitude within a range to 1
// Useful for climbing frequency effects as in "Contact" by Daft Punk
class SPAHillEffect : public SignalProcessingAlgorithm
{
public: 
	std::string convertToBits(const double* dataToConvert, int noiseFloor);
};