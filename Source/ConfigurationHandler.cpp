#include "stdafx.h"
#include "ConfigurationHandler.h"

ConfigurationHandler::ConfigurationHandler(std::string configFileDirectory, std::string configFileName)
	: _arfwriterMode(EMC_Mode::Read), 
	  _configurationDirectory(configFileDirectory),
	  _configurationFileName(configFileName)
{
	_decodedJSON = new Json::Value();
	LoadConfigurationFile(configFileDirectory + configFileName);
}

// Load in the JSON Configuration file at the specified path
void ConfigurationHandler::LoadConfigurationFile(std::string configurationFilePath)
{	
	std::ifstream in(configurationFilePath);
	Json::Reader reader;
	reader.parse(in, _decodedJSON);

	// Default to Read Mode
	_arfwriterMode = EMC_Mode::Read;

	// TODO: Refactor
	if (_decodedJSON["mode"].asString().compare("write") == 0)
	{
		_arfwriterMode = EMC_Mode::Decode;
	}
}

void ConfigurationHandler::HashConfigField(std::string field)
{
	// TODO
}

EMC_Mode ConfigurationHandler::GetMode()
{
	return _arfwriterMode;
}

// Returns the filename of the song in the configuration file
std::string ConfigurationHandler::GetFilename()
{
	return _decodedJSON["filename"].asString();
}

// Returns the file path of the working directory
std::string ConfigurationHandler::GetDirectory()
{
	return _configurationDirectory;
}

// TODO:  Heavy Refactoring
void ConfigurationHandler::InitializeAnalyzer(ArduinoReadableFileWriter& arf)
{
    Json::Value::iterator it = _decodedJSON["algorithms"].begin();

	// Each loop corresponds to a subnode in the "algorithms" node
	while (it != _decodedJSON["algorithms"].end())
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
        arf.AddFrequencyRange((*it)["range"][0].asInt(), (*it)["range"][1].asInt(), fixedBoundaryType, *spa);
        ++it;
    }
}