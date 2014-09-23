#include "stdafx.h"

class SignalProcessingAlgorithm
{
public:
	SignalProcessingAlgorithm();
	~SignalProcessingAlgorithm();
	
	// Define lower and upper bounds (as indices) for this processor
	void setBounds(const int lower, const int upper);
	
	// Heart and soul of the Signal Processing Algorithm
	virtual std::string convertToBits(const double* dataToConvert, int noiseFloor);
	
protected:
	int lowerBound_, upperBound_, bits_;

private:
	bool checkBit(const double* dataToConvert, int bit, int noiseFloor);
};

//=====================
// SUBCLASSES BELOW...
//=====================

// Watches Intensity of a specific frequency range; returns 1 bit
class SPAIntensity : public SignalProcessingAlgorithm
{
public:
	std::string convertToBits(const double* dataToConvert, int noiseFloor);
};

// ---
 // Watches only an exact frequency; returns 1 bit
class SPAWatchFrequency : public SignalProcessingAlgorithm
{
public:
	std::string convertToBits(const double* dataToConvert, int noiseFloor);
	void setWatchFrequency(double watchFrequency);

private:
	int watchBound_;
};

// Watches for percussion and does specific things for them. I want this to be configurable.
// For instance, on HATS make all bits go to a value of 1, or etc.
class SPAPercussion : public SignalProcessingAlgorithm
{
public:
	std::string convertToBits(const double* dataToConvert, int noiseFloor);

	// CONFIG STUFF
};

// Turns all bits lower than the maximum amplitude within a range to 1
// Useful for climbing frequency effects as in "Contact" by Daft Punk
class SPAHillEffect : public SignalProcessingAlgorithm
{
public: 
	std::string convertToBits(const double* dataToConvert, int noiseFloor); // If false, determines frequency based on Maximum Amplitude
};