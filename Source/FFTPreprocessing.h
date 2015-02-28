#include "stdafx.h"
#include "fftw3.h"
#include "FrequencyMaximum.h"
#include "MP3toData.h"
#include "ConfigurationHandler.h"
#include <thread>
#include <chrono>

void convertMP3ToARF(ConfigurationHandler& configHandler);
void readARF(ConfigurationHandler& configHandler);

// FFT PreProcessing
void copyVectorToPointerArray(DataSet& vectorIn, double* arrayOut);
double hanningMultiplier(int indexOfHanningFunction);
void normalize(DataSet& data);
void applyHanningWindow(DataSet& dataIn);
DataSet prepareAndExecuteFFT(DataSet& dataIn, fftw_plan& fft_plan, double* workingDoubleArray_, fftw_complex* complexResults);

// Fast Fourier Transform
DataSet fastFourierTransform(DataSet& data, fftw_plan& fft_plan, double* workingDoubleArray_, fftw_complex* complexResults);

// More Tests 2
long captureFileData(std::string songName, AudioFileData& waveformDataPoints);