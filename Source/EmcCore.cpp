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
	MusicFileOperations::ConvertMP3ToARF(_configHandler.GetDirectory(), _configHandler.GetFilename());
	StartAnalyses();
}

// Read Workflow
void EmcCore::Read()
{
	auto arFileName = CoreMath::ChangeFileExtension(_configHandler.GetFullPath(), AR_FILE_EXTENSION);

	std::ifstream visualizationFile(arFileName);
	if (visualizationFile.is_open())
	{
		std::string line;
		auto start = std::chrono::high_resolution_clock::now();
		while (std::getline(visualizationFile, line))
		{
			std::cerr << line << "\n";
			std::this_thread::sleep_until(start + std::chrono::microseconds(45000));
			start = std::chrono::high_resolution_clock::now();
			//while (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() < 46447);
		}
	}
}