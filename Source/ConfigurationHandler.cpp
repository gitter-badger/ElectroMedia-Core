#include "stdafx.h"
#include "ConfigurationHandler.h"

ConfigurationHandler::ConfigurationHandler(ArduinoReadableFileWriter& arf)
    :arf_(arf)
{}

void ConfigurationHandler::loadInConfigurationSettings()
{
    std::ifstream in(CONFIGURATION_FILE_NAME);
    Json::Value root;

    in >> root;

    initializeSignalProcessingAlgorithms(root);
}

void ConfigurationHandler::initializeSignalProcessingAlgorithms(Json::Value root)
{
    Json::Value::iterator it = root["algorithms"].begin();

    while (it != root["algorithms"].end())
    {
        SignalProcessingAlgorithm* spa;
        auto fixedBoundaryType = 0;
        auto fixedBoundary = (*it)["fixedBoundary"].asString();
        auto type = (*it)["type"].asString();
        auto bits = (*it)["bits"].asInt();

        if (type == "direct")
        {
            spa = new SignalProcessingAlgorithm(bits);
        }
        else// if (type == "hill")
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

        arf_.addFrequencyRange((*it)["range"][0].asInt(), (*it)["range"][1].asInt(), fixedBoundaryType, *spa);
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