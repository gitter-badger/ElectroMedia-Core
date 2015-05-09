#include "stdafx.h"
#include "ConfigurationHandler.h"

ConfigurationHandler::ConfigurationHandler(std::string configFilePath)
	: arfwriterMode(EMC_Mode::Read), 
	_configurationFilePath(configFilePath)
{
	auto nameWithoutExtension = std::string(configFilePath.begin(), extensionLocation + configFilePath.begin());
	decodedJSON = new Json::Value();
	loadConfigurationFile(configFilePath);
}

// Load in the JSON Configuration file at the specified path
void ConfigurationHandler::loadConfigurationFile(std::string configurationFilePath)
{	
	std::ifstream in(configurationFilePath);
	Json::Reader reader;
	reader.parse(in, decodedJSON);

	// Default to Read Mode
	arfwriterMode = EMC_Mode::Read;

	// TODO: Refactor
	if (decodedJSON["mode"].asString().compare("write") == 0)
	{
		arfwriterMode = EMC_Mode::Decode;
	}
}

EMC_Mode ConfigurationHandler::getMode()
{
	return arfwriterMode;
}

// Returns the filename of the song in the configuration file
std::string ConfigurationHandler::getFilename()
{
	return decodedJSON["filename"].asString();
}

// Returns the file path of the working directory
std::string ConfigurationHandler::getDirectory()
{
	return workingDirectory;
}

// TODO:  Heavy Refactoring
void ConfigurationHandler::initializeAnalyzer(ArduinoReadableFileWriter& arf)
{
    Json::Value::iterator it = decodedJSON["algorithms"].begin();

	// Each loop corresponds to a subnode in the "algorithms" node
	while (it != decodedJSON["algorithms"].end())
    {
        Analyzer* spa;
        auto fixedBoundaryType = 0;
        auto fixedBoundary = (*it)["fixed_boundary"].asString();
        auto type = (*it)["type"].asString();
        auto bits = (*it)["bits"].asInt();

		// Change the following to something like Spring
        if (type == "direct")
        {
            spa = new Analyzer(bits);
        }
		else if (type == "pca")
		{
			spa = new FeatureExtractionAnalyzer();
		}
        else
        {
            spa = new HillEffectAnalyzer();
        }

		// This really just shouldn't exist 
        if (fixedBoundary == "upper")
        {
            fixedBoundaryType = ADJUSTMENT_TYPE_CHANGE_LOWER;
        }
        else if (fixedBoundary == "lower")
        {
            fixedBoundaryType = ADJUSTMENT_TYPE_CHANGE_UPPER;
        }
        else fixedBoundaryType = ADJUSTMENT_TYPE_CENTER;

		// Why do frequency ranges exist again?
        arf.addFrequencyRange((*it)["range"][0].asInt(), (*it)["range"][1].asInt(), fixedBoundaryType, *spa);
        ++it;
    }
}