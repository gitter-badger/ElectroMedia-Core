#include "stdafx.h"
#include "EmcCore.h"

EmcCore::EmcCore(std::string configuration_file_path)
	: configuration_handler_(new ConfigurationHandler(configuration_file_path, EmcCore::kConfigurationFileName))
{
}

EmcCore::~EmcCore()
{
	delete analyzer_collection_;
	analyzer_collection_ = NULL;
}

void EmcCore::Run()
{
	// Call the appropriate static functions
	switch (configuration_handler_->GetMode())
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
	analyzer_collection_->push_back(std::make_shared<Analyzer*>(analyzer));
}

void EmcCore::StartAnalyses()
{
	// Spin off a thread for each of the analyses
}

// Decode Workflow
void EmcCore::Decode()
{
	MusicFileOperations::ConvertMP3ToARF(configuration_handler_->GetDirectory(), configuration_handler_->GetFilename());
	StartAnalyses();
}

// Read Workflow
void EmcCore::Read()
{
	auto arFileName = CoreMath::ChangeFileExtension(configuration_handler_->GetFullPath(), AR_FILE_EXTENSION);

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