#include "stdafx.h"
#include "Constants.h"
#include "MusicFileOperations.h"
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
	auto configHandler = new ConfigurationHandler(getPath(basePath), "config.json");

	// Determine the desired operation
	switch (configHandler->GetMode())
	{
	case EMC_Mode::Decode:
		CoreMath::Debug("Preparing to decode the file.");
		MusicFileOperations::ConvertMP3ToARF(*configHandler);
		break;

	case EMC_Mode::Read:
		CoreMath::Debug("Preparing to read the file.");
		MusicFileOperations::ReadArFile(*configHandler);
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