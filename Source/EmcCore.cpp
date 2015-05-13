#include "stdafx.h"
#include "EmcCore.h"

EmcCore::EmcCore(std::string configurationFilePath)
	: _configHandler( *(new ConfigurationHandler(configurationFilePath,"config.json")) )
{
}

EmcCore::~EmcCore()
{
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

void EmcCore::AddAnalyzer(Analyzer* analyzer)
{
	_analyzers->push_back( std::make_shared<Analyzer*>(analyzer) );
}

void EmcCore::StartAnalyses()
{
	// Spin off a thread for each of the analyses
}

// Decode Workflow
void EmcCore::Decode()
{
	MusicFileOperations::ConvertMP3ToARF(_configHandler);
	StartAnalyses();
}

// Read Workflow
void EmcCore::Read()
{
	MusicFileOperations::ReadArFile(_configHandler);
}