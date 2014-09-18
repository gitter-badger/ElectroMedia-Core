#include "stdafx.h"

// Basic methods which convert an integer index to a frequency value, or vice versa
int convertFrequencyToInt(double frequencyBand);
double convertIntToFrequency(int index);

// Used to calculate a dynamic noise floor, taking fluctuations in signal noise
// and amplitude changes into consideration. Returns an integer value which 
// corresponds to noise floor amplitude
int calculateDynamicNoiseFloor(double* data, int lowerBound, int upperBound);

// Pipes out a line of text to cerr if and only if DEBUG_ENABLED == true
void debug(std::string debugComment); //