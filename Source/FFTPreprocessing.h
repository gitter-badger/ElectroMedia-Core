#include "stdafx.h"
#include "fftw3.h"
#include "FrequencyMaximum.h"

// FFT PreProcessing
void copyVectorToPointerArray(dataSet& vectorIn, double* arrayOut);
double hanningMultiplier(int indexOfHanningFunction);
void normalize(dataSet& data);
void applyHanningWindow(dataSet& dataIn);
dataSet prepareAndExecuteFFT(dataSet& dataIn, fftw_plan& fft_plan, double* workingDoubleArray_, fftw_complex* complexResults);

// Fast Fourier Transform
dataSet fastFourierTransform(dataSet& data, fftw_plan& fft_plan, double* workingDoubleArray_, fftw_complex* complexResults);

// More Tests 2
long calculateDataFileSize(char fileName[], dataSet& waveformDataPoints);