#include "stdafx.h"
#include "ArduinoReadableFileWriter.h"
#include "EMCModes.h"
#include "FeatureExtractionAnalyzer.h"
#include "HillEffectAnalyzer.h"
#include "Dependencies\json\json.h"

/* 
 *  Being Refactored!
 */

class ConfigurationHandler
{
public:
    // Constructors / Destructors
	ConfigurationHandler(std::string configFileDirectory, std::string configFileName);
    ~ConfigurationHandler();

	// Getters
	std::string getFilename();
	std::string getDirectory();
	EMC_Mode getMode();

	// Initialize the ArduinoReadableFileWriter object with the SPAs declared in the JSON
	void initializeAnalyzer(ArduinoReadableFileWriter& arf);

private:
	// Load in the configuration JSON at specified file path
	void loadConfigurationFile(std::string configurationFilePath);

	// Private Variables
	EMC_Mode arfwriterMode;
	Json::Value decodedJSON;
	
	// PostRefactor
	std::string _configurationDirectory;
	std::string _configurationFileName;
};