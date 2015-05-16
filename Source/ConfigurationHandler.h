#include "stdafx.h"
#include "ArduinoReadableFileWriter.h"
#include "EMCModes.h"
#include "AnalyzerFactory.h"
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
	std::string GetFullPath();
	EMC_Mode GetMode();

	// Initialize the ArduinoReadableFileWriter object with the SPAs declared in the JSON
	void InitializeAnalyzer(ArduinoReadableFileWriter& arf); // DEPRECATED

	vector< std::shared_ptr<Analyzer*> >* GetAnalyzers();

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

	AnalyzerFactory _factory;
};

#endif