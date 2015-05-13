#include "stdafx.h"
#include "CoreMath.h"
#include "EmcCore.h"

// Signed 16-bit PCM Little-Endian
// Command line 

std::string getPath(char* basePath);

int main(int argc, char *argv[])
{
	// Get the Base Path of the EMC executable
	char basePath[255] = "";
	_fullpath(basePath, argv[0], sizeof(basePath));
	auto configurationFilePath = CoreMath::GetPath(basePath);

	// Start up EMC and run it
	auto emc = new EmcCore(configurationFilePath);
	emc->Run();

	return 1;
}