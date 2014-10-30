#include "stdafx.h"
#include "fftw3.h"
#include "FrequencyMaximum.h"

// FFT PreProcessing

double hanningMultiplier(int indexOfHanningFunction);
vector<double>* copyAndPadData(vector<double> dataIn);
vector<double>* normalize(vector<double> data);
vector<double>* applyHanningWindow(vector<double> dataIn);
vector<double>* prepareAndExecuteFFT(vector<double> dataIn);

// Fast Fourier Transform
fftw_complex* fastFourierTransform(vector<double> dataIn);

// More Tests 2
long calculateDataFileSize(char fileName[]);
vector<double>* obtainDataFromFile(char fileName[], long fileSize);