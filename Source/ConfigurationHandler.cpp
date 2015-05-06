#include "stdafx.h"
#include "ConfigurationHandler.h"

ConfigurationHandler::ConfigurationHandler(std::string configDirectory, std::string filename)
: arfwriterMode(MODE_WRITE), workingDirectory(configDirectory)
{
	decodedJSON = new Json::Value();
	loadConfigurationFile(configDirectory + filename);
}

// Load in the JSON Configuration file at the specified path
void ConfigurationHandler::loadConfigurationFile(std::string configurationFilePath)
{	
	std::ifstream in(configurationFilePath);
	Json::Reader reader;
	reader.parse(in, decodedJSON);

	// Default to Read Mode
	arfwriterMode = MODE_READ;

	// TODO: Refactor
	if (decodedJSON["mode"].asString().compare("write") == 0)
	{
		arfwriterMode = MODE_WRITE;
	}
}

// Returns what Mode Enum we're currently running
// TODO: Refactor
int ConfigurationHandler::getMode()
{
	return (int)arfwriterMode;
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
			spa = new SPAToPCAExperiment();
		}
        else
        {
            spa = new SPAHillEffect();
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