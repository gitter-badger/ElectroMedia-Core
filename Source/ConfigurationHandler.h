#include "stdafx.h"
#include "ArduinoReadableFileWriter.h"
#include "EMCModes.h"
#include "FeatureExtractionAnalyzer.h"
#include "HillEffectAnalyzer.h"
#include "Dependencies\json\json.h"

#ifndef ConfigurationHandlerDefinition
#define ConfigurationHandlerDefinition

class ConfigurationHandler
{
public:
    // Constructors / Destructors
	ConfigurationHandler(std::string configFileDirectory, std::string configFileName);
    ~ConfigurationHandler();

	// Getters
	std::string GetFilename();
	std::string GetDirectory();
	EMC_Mode GetMode();

	// Initialize the ArduinoReadableFileWriter object with the SPAs declared in the JSON
	void InitializeAnalyzer(ArduinoReadableFileWriter& arf);

private:
	// Load in the configuration JSON at specified file path
	void LoadConfigurationFile(std::string configurationFilePath);
	void HashConfigField(std::string field);

	// Private Variables
	EMC_Mode	_arfwriterMode;
	Json::Value _decodedJSON;
	
	// PostRefactor
	std::string _configurationDirectory;
	std::string _configurationFileName;
};

#endif