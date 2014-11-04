#include "stdafx.h"
#include "FFTPreprocessing.h"

/*
 * Note 03 == Need to add more comments and clean up the general progam flow a bit
 *
 * Note 04 == Come up with a better, more intuitive flow to add FRPs. Especially
 *            with respect to setting bits
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

    convertMP3ToARF(argv[1]);

    return 1;
}