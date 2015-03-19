#include "stdafx.h"
#include "ConfigurationHandler.h"

ConfigurationHandler::ConfigurationHandler(std::string configDirectory, std::string filename)
: arfwriterMode(MODE_WRITE), workingDirectory(configDirectory)
{
	decodedJSON = new Json::Value();
	loadConfigurationFile(configDirectory + filename);
}

void ConfigurationHandler::loadConfigurationFile(std::string configurationFileName)
{	
	std::ifstream in(configurationFileName);
	Json::Reader reader;
	reader.parse(in, decodedJSON);

	if (decodedJSON["mode"].asString().compare("write") == 0) // Remove Hardcoded values
	{
	arfwriterMode = MODE_WRITE;
		return;
	}

	arfwriterMode = MODE_READ;
}

int ConfigurationHandler::getMode()
{
	return (int)arfwriterMode;
}

std::string ConfigurationHandler::getFilename()
{
	return decodedJSON["filename"].asString();
}

std::string ConfigurationHandler::getDirectory()
{
	return workingDirectory;
}

void ConfigurationHandler::initializeSignalProcessingAlgorithms(ArduinoReadableFileWriter& arf)
{
    Json::Value::iterator it = decodedJSON["algorithms"].begin();

	while (it != decodedJSON["algorithms"].end())
    {
        SignalProcessingAlgorithm* spa;
        auto fixedBoundaryType = 0;
        auto fixedBoundary = (*it)["fixed_boundary"].asString();
        auto type = (*it)["type"].asString();
        auto bits = (*it)["bits"].asInt();

        if (type == "direct")
        {
            spa = new SignalProcessingAlgorithm(bits);
        }
		else if (type == "pca")
		{
			spa = new SPAToPCAExperiment();
		}
        else
        {
            spa = new SPAHillEffect();
        }

        if (fixedBoundary == "upper")
        {
            fixedBoundaryType = ADJUSTMENT_TYPE_CHANGE_LOWER;
        }
        else if (fixedBoundary == "lower")
        {
            fixedBoundaryType = ADJUSTMENT_TYPE_CHANGE_UPPER;
        }
        else fixedBoundaryType = ADJUSTMENT_TYPE_CENTER;

        arf.addFrequencyRange((*it)["range"][0].asInt(), (*it)["range"][1].asInt(), fixedBoundaryType, *spa);
        ++it;
    }
}