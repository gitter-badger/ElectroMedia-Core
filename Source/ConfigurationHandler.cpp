#include "stdafx.h"
#include "ConfigurationHandler.h"

ConfigurationHandler::ConfigurationHandler()
{}

void ConfigurationHandler::loadConfigurationFile(std::string configurationFileName)
{
	this->configurationFilename = configurationFileName;
}

std::string ConfigurationHandler::getFilename()
{
	std::ifstream in(configurationFilename);
	Json::Value root;
	Json::Reader reader;
	reader.parse(in, root);

	return root["filename"].asString();
}

void ConfigurationHandler::initializeSignalProcessingAlgorithms(ArduinoReadableFileWriter& arf)
{
	std::ifstream in(configurationFilename);
	Json::Value root;
	Json::Reader reader;
	reader.parse(in, root);

    Json::Value::iterator it = root["algorithms"].begin();

	while (it != root["algorithms"].end())
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

void ConfigurationHandler::generateDefault()
{
    debug("Generating a new configuration file");

    std::ofstream newConfigFile;
    newConfigFile.open(CONFIGURATION_FILE_NAME, std::ios::out);
    newConfigFile << "spa-8::50:200+0\nspa-8::200:400+2\nspa-8::300:600+2\nspa-8::200:1000+1";
    newConfigFile.close();
}