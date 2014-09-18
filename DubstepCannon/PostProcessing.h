/**
 *	PostProcessing.h
 *
 *  THIS PACKAGE IS FOR REFRENCE ONLY!!!
 *  It has been marked for deletion and will be removed soon.
 */


#include "stdafx.h"
#include "SignalProcessing.h"
#include <vector>

FrequencyMaximum* AnalyzeBand(double* data, int windowWidth, double* frequencyBand, int numMaxima);
double calculateIntensity(double* data, double* frequencyBand);
char* MaximumtoString(double frequency);

// Bad function; needs to be rewritten
double* ToByte(double* data, double* frequencyBand, int numBytes);