#include "stdafx.h"
#include "CoreMath.h"
#include "EmcCore.h"

// Signed 16-bit PCM Little-Endian
// Command line 

int main(int argc, char *argv[])
{
	// Get the Base Path of the EMC executable
	char base_path[255] = "";
	_fullpath(base_path, argv[0], sizeof(base_path));
	auto configuration_file_path = CoreMath::GetPath(base_path);

	// Start up EMC and run it
	auto emc = new EmcCore(configuration_file_path);
	emc->Run();

	return 1;
}