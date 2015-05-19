#include "stdafx.h"
#include "fftw3.h"
#include "CoreMath.h"
#include "MP3toData.h"
#include "Constants.h"
#include "EmcSettings.h"
#include <chrono>

#ifndef EMC_MusicFileOperations_H_
#define EMC_MusicFileOperations_H_ 

static class MusicFileOperations
{
	typedef std::shared_ptr<std::vector<char>> MP3FileData;

public:
	static void ConvertMP3ToARF();
	
private:
	// FFT PreProcessing
	static void CopyVectorToPointerArray(DataSet& vector_in, double* array_out);
	static double GetHanningMultiplier(int index_at);
	static void Normalize(DataSet& data);
	static void ApplyHanningWindow(DataSet& data);
	static DataSet PrepareAndExecuteFFT(DataSet& data, fftw_plan& fft_plan, double* working_array, 
		fftw_complex* complex_fft_results);

	// Fast Fourier Transform
	static DataSet ExecuteFastFourierTransform(DataSet& data, fftw_plan& fft_plan, double* working_array,
		fftw_complex* complex_fft_results);

	static MP3FileData GetDataFromMP3();
	static long CaptureFileData(AudioFileData& waveform_data);
};

#endif
