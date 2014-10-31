#include "stdafx.h"
#include "fftw3.h"
#include "FrequencyMaximum.h"

// FFT PreProcessing
void convertVectorToPointerArray(dataSet& vectorIn, double* arrayOut);
double hanningMultiplier(int indexOfHanningFunction);
dataSet copyAndPadData(dataSet& dataIn);
dataSet normalize(dataSet& data);
dataSet applyHanningWindow(dataSet& dataIn);
dataSet prepareAndExecuteFFT(dataSet& dataIn);

// Fast Fourier Transform
fftw_complex* fastFourierTransform(dataSet& dataIn);

// More Tests 2
long calculateDataFileSize(char fileName[]);
double* obtainDataFromFile(char fileName[], long fileSize);