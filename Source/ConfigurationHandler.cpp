#include "stdafx.h"
#include "ConfigurationHandler.h"
#include <sstream>
#include <regex>

ConfigurationHandler::ConfigurationHandler(ArduinoReadableFileWriter& arf)
    :arf_(arf)
{}

void ConfigurationHandler::addFrequencyRangeFromConfig(std::string spaString)
{
    std::regex numberRegex("[0-9]+");

    std::sregex_iterator ia(spaString.begin(), spaString.end(), numberRegex);
    std::sregex_iterator it_end;
    auto configVals = new int[4];
    int index = 0;
    while (ia != it_end && index < 4)
    {
        auto iab = std::string((*ia)[0]);
        std::stringstream val(iab);
        int result;
        configVals[index++] = (val >> result ? result : 0);
        ++ia;
    }
    auto spa = new SignalProcessingAlgorithm(configVals[0]);
    arf_.addFrequencyRange(configVals[1], configVals[2], configVals[3], *spa);
}

void ConfigurationHandler::loadInConfigurationSettings()
{
    std::ifstream configFile(CONFIGURATION_FILE_NAME);
    if (configFile.is_open())
    {
        std::string line;
        std::getline(configFile, line);//"spa-4::50:200+0spa-8::200:400+2spa-8::300:600+2spa-16::200:100+1";
        std::regex spaRegex("spa-[0-9]*::[0-9]*:[0-9]*[+][0-2]");
        std::string substring = "";
        std::smatch match;

        const std::sregex_token_iterator end;
        std::sregex_token_iterator it(line.begin(), line.end(), spaRegex);
        for (; it != end; ++it)
        {
            addFrequencyRangeFromConfig(*it);
        }

        configFile.close();
    }
    else generateDefault();
}

void ConfigurationHandler::generateDefault()
{
    debug("Generating a new configuration file");

    std::ofstream newConfigFile;
    newConfigFile.open(CONFIGURATION_FILE_NAME);
    newConfigFile << "spa-8::50:200+0spa-8::200:400+2spa-8::300:600+2spa-8::200:1000+1";
    newConfigFile.close();
}