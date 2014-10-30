// DubstepCannon.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "MP3toData.h"
#include "FFTPreprocessing.h"
#include "ArduinoReadableFileWriter.h"
#include <cmath>

// Signed 16-bit PCM Little-Endian

// MAIN -- This is the primary loop for the EMusic Cannon. This will invoke several
// other functions, but the bulk of the data interpretation starts here.
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
    long filesize = calculateDataFileSize((char*)DECODED_FILE_NAME.c_str());
    vector<double> dataFromFile = *obtainDataFromFile((char*)DECODED_FILE_NAME.c_str(), filesize);

   /* for (int i = 0; i < filesize; i++)
    {
        cout << i << " " << dataFromFile[i] << "\n";
    }*/

    int sweeps = -1;

    // preProcessData is an empty integer array that is used to receive data via memcpy.
    // It is rewritten in every loop, whereas dataFromFile is constant.
    vector<double> preProcessData(WINDOW_SIZE);

    //cout << "The number of samples in this file is " << filesize/sizeof(int) << endl;

    cout << "Beginning song to *.arf process...\n";
  //  while((++sweeps)*WINDOW_SHIFT_AMOUNT < (filesize/sizeof(int) - SONG_ENDING_PAD*WINDOW_SHIFT_AMOUNT))
    //{
        int index = 0;

        // Switch pointer's location in memory to the location of the new window, then copy from
        // that point in memory through the length of the WINDOW_SIZE in integers
        auto shiftedWindowOrigin_ = sweeps * WINDOW_SHIFT_AMOUNT;


        vector<double>::iterator it = dataFromFile.begin();
       // it += shiftedWindowOrigin_;

        while (it != dataFromFile.end() && index < WINDOW_SIZE)
        { // Vector Subscript out of range
            preProcessData[index++] = (double) dataFromFile[index];
            ++it;
        }



        // memcpy(preProcessData, shiftedWindowOrigin_,sizeof(int)*WINDOW_SIZE);

        // FFT STUFF HERE
        auto dataFromFFT = prepareAndExecuteFFT(preProcessData);
        arfile.write(*dataFromFFT);
  //  }

    cout << "Process complete.\n";

    // Garbage Collection -- deallocate
    arfile.close();

    return 1;
}