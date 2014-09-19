#include "stdafx.h"

class SignalProcessingAlgorithm
{
public:
	SignalProcessingAlgorithm();
	~SignalProcessingAlgorithm();
	SignalProcessingAlgorithm& operator=(const SignalProcessingAlgorithm& other);
	
	// Heart and soul of the Signal Processing Algorithm
	virtual std::string convertToBits(double* dataToConvert, int noiseFloor);
	void setBounds(int lower, int upper);

protected:
	int lowerBound_, upperBound_, bits_;
};

//=====================
// SUBCLASSES BELOW...
//=====================

// Watches Intensity of a specific frequency range; returns 1 bit
class SPAIntensity : public SignalProcessingAlgorithm
{
public:
	std::string convertToBits(double* dataToConvert, int noiseFloor) override;
};

 // Watches only an exact frequency; returns 1 bit
class SPAWatchFrequency : public SignalProcessingAlgorithm
{
public:
	std::string convertToBits(double* dataToConvert, int noiseFloor) override;
	void setWatchFrequency(double watchFrequency);

private:
	int watchBound_;
};

// Watches for percussion and does specific things for them. I want this to be configurable.
// For instance, on HATS make all bits go to a value of 1, or etc.
class SPAPercussion : public SignalProcessingAlgorithm
{
public:
	std::string convertToBits(double* dataToConvert, int noiseFloor) override;

	// CONFIG STUFF
};

// Turns all bits lower than the maximum amplitude within a range to 1
// Useful for climbing frequency effects as in "Contact" by Daft Punk
class SPAHillEffect : public SignalProcessingAlgorithm
{
public: 
	std::string convertToBits(double* dataToConvert, int noiseFloor) override;
};