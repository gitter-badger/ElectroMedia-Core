#include "stdafx.h"
#include "MP3toData.h"
#include "FFTPreprocessing.h"
#include "ArduinoReadableFileWriter.h"
#include <cmath>

/*
 * Note 03 == Need to add more comments and clean up the general progam flow a bit
 */

// Signed 16-bit PCM Little-Endian

int main(int argc, char *argv[], char *envp[])
{
    // We absolutely require at least two arguments, as the second is the filename.
    // If we are not given that second argument, error out and return.
    if(argc < 2) 
    {     
        cout << "ERROR: You must specify a .mp3 file for decoding!\n";
        return -1; 
    }

    // Prepare the filename
    char filename[20];
    strcpy(filename, argv[1]);
    strcat(filename, ".arf");

    // Open the ARF Writer object
    ArduinoReadableFileWriter arfile = ArduinoReadableFileWriter(filename);
    arfile.setMode(arfile.MODE_TEXT);

    // Process the MP3 File
    decodeMusic(argv[1]);

    // Process the raw data file and put the data into fulldata
    dataSet dataFromFile = std::make_shared<vector<double>>();

    long filesize = calculateDataFileSize((char*)DECODED_FILE_NAME.c_str(), dataFromFile);
    int sweeps = -1;

    // preProcessData is an empty integer array that is used to receive data via memcpy.
    // It is rewritten in every loop, whereas dataFromFile is constant.
    dataSet preProcessData = dataSet();

    vector<double>::const_iterator first;
    vector<double>::const_iterator last;

    double* workingDoubleArray_ = (double*)fftw_malloc(sizeof(double) * WINDOW_SIZE);
    fftw_complex* complexResults = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * WINDOW_SIZE);
    fftw_plan new_plan = fftw_plan_dft_r2c_1d(WINDOW_SIZE, workingDoubleArray_, complexResults, FFTW_MEASURE);
    //cout << "The number of samples in this file is " << filesize/sizeof(int) << endl;

    cout << "Beginning song to *.arf process...\n";
    while((++sweeps)*WINDOW_SHIFT_AMOUNT < (filesize/sizeof(int) - SONG_ENDING_PAD*WINDOW_SHIFT_AMOUNT))
    {
        std::cerr << dataFromFile->size() << ":  " << sweeps*WINDOW_SHIFT_AMOUNT << " to " << sweeps*WINDOW_SHIFT_AMOUNT + WINDOW_SIZE << endl;
        first = dataFromFile->begin() + sweeps*WINDOW_SHIFT_AMOUNT;
        last = dataFromFile->begin() + sweeps*WINDOW_SHIFT_AMOUNT + WINDOW_SIZE;
        vector<double> windowedSubvector(first, last);
        preProcessData = std::make_shared<vector<double>>(windowedSubvector);

        // FFT STUFF HERE
        auto dataFromFFT = prepareAndExecuteFFT(preProcessData,new_plan,workingDoubleArray_,complexResults);
        arfile.write(dataFromFFT);
    }
    cout << "Process complete.\n";
    fftw_destroy_plan(new_plan);
    fftw_free(workingDoubleArray_);
    fftw_free(complexResults);
    fftw_cleanup();
    arfile.close();

    return 1;
}