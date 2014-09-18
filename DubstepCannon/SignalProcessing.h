#include "stdafx.h"
#include "fftw3.h"
#include "FrequencyMaximum.h"

// Pre Processing

void copyAndPadData(const double* dataIn, double* dataOut);
void normalize(double* data);
double hanningMultiplier(int indexOfHanningFunction);
double* applyHanningWindow(const int* dataIn);
double* prepareAndExecuteFFT(const int* dataIn);

fftw_complex* fastFourierTransform(const double* data);

long calculateDataFileSize(char* fileName);
int* obtainDataFromFile(char* fileName, long fileSize);