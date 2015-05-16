#include "stdafx.h"
#include "fftw3.h"
#include "CoreMath.h"
#include "FrequencyMaximum.h"
#include "MP3toData.h"
#include "ConfigurationHandler.h"
#include "Constants.h"
#include "FFmpegReturnValues.h"
#include <thread>
#include <chrono>

static class MusicFileOperations
{
	typedef std::shared_ptr<std::vector<char>> MP3FileData;

public:
	static void ConvertMP3ToARF(std::string directory, std::string nameWithoutExtension);
	static void ReadArFile(ConfigurationHandler& configHandler);
	
private:
	// FFT PreProcessing
	static void CopyVectorToPointerArray(DataSet& vectorIn, double* arrayOut);
	static double GetHanningMultiplier(int indexOfHanningFunction);
	static void Normalize(DataSet& data);
	static void ApplyHanningWindow(DataSet& dataIn);
	static DataSet PrepareAndExecuteFFT(DataSet& dataIn, fftw_plan& fft_plan, double* workingDoubleArray_, fftw_complex* complexResults);

	// Fast Fourier Transform
	static DataSet ExecuteFastFourierTransform(DataSet& data, fftw_plan& fft_plan, double* workingDoubleArray_, fftw_complex* complexResults);


	static MP3FileData GetDataFromMP3(std::string directory, std::string nameWithoutExtension);
	static long CaptureFileData(std::string songName, AudioFileData& waveformDataPoints);
};
