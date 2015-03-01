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

std::string getPath(char* basePath);

int main(int argc, char *argv[], char *envp[])
{
	char basePath[255] = "";
	_fullpath(basePath, argv[0], sizeof(basePath));

	auto configHandler = new ConfigurationHandler(getPath(basePath), "config.json");
		
	if (configHandler->getMode() == 0)
	{
		debug("Preparing to convert...");
		convertMP3ToARF(*configHandler);
	}
	else readARF(*configHandler);

	return 1;
}

std::string getPath(char* basePath)
{
	std::string path = (std::string)basePath;

	auto exeLocation = ((std::string)path).find("EMC.exe");
	return std::string(path.begin(), exeLocation + path.begin());
}