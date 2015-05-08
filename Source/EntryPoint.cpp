#include "stdafx.h"
#include "Constants.h"
#include "FFTPreprocessing.h"
#include "EMCModes.h"

// Signed 16-bit PCM Little-Endian
// Command line 

std::string getPath(char* basePath);

int main(int argc, char *argv[])
{
	// Get the Base Path of the EMC executable
	char basePath[255] = "";
	_fullpath(basePath, argv[0], sizeof(basePath));

	// Get the location of the config.json, then create a Configuration Handler
	auto configFilePath = getPath(basePath) + "config.json";
	auto configHandler = new ConfigurationHandler(configFilePath);

	// Determine the desired operation
	switch (configHandler->getMode())
	{
	case EMC_Mode::Decode:
		debug("Preparing to decode the file.");
		convertMP3ToARF(*configHandler);
		break;

	case EMC_Mode::Read:
		debug("Preparing to read the file.");
		readARF(*configHandler);
		break;
	}

	return 1;
}

std::string getPath(char* basePath)
{
	std::string path = (std::string)basePath;

	auto exeLocation = ((std::string)path).find("EMC.exe");
	return std::string(path.begin(), exeLocation + path.begin());
}