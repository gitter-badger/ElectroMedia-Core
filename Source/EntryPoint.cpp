#include "stdafx.h"
#include "FFTPreprocessing.h"

/*
 * Note 03 == Need to add more comments and clean up the general progam flow a bit
 *
 * Note 04 == Come up with a better, more intuitive flow to add FRPs. Especially
 *            with respect to setting bits
 */

// Signed 16-bit PCM Little-Endian
// Command line 

int main(int argc, char *argv[], char *envp[])
{
	auto configHandler = new ConfigurationHandler();
	configHandler->loadConfigurationFile("F:\\Projects\\EMC\\Debug\\config.json");
	convertMP3ToARF(*configHandler);

	return 1;
}