#include "stdafx.h"
#include "EmcCore.h"


EmcCore::EmcCore(std::string configurationFilePath)
	: _configHandler( *(new ConfigurationHandler(configurationFilePath,"config.json")) )
{
}

EmcCore::~EmcCore()
{
	delete &_configHandler;
	delete _analyzers;
	_analyzers = NULL;
}


void EmcCore::Run()
{
	// Call the appropriate static functions
	switch (_configHandler.GetMode())
	{
	case EMC_Mode::Decode:
		CoreMath::Debug("Preparing to decode the file.");
		Decode();
		break;

	case EMC_Mode::Read:
		CoreMath::Debug("Preparing to read the file.");
		Read();
		break;
	}
}

void EmcCore::Decode()
{
	MusicFileOperations::ConvertMP3ToARF(_configHandler);

	// Do stuff with Analyzers here
}

void EmcCore::Read()
{
	MusicFileOperations::ReadArFile(_configHandler);
}