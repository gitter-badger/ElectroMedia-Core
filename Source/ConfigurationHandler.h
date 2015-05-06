#include "stdafx.h"
#include "ArduinoReadableFileWriter.h"
#include "Dependencies\json\json.h"

/* 
 *  Being Refactored!
 */


class ConfigurationHandler
{
public:
    // Constructors / Destructors
	ConfigurationHandler(std::string configDirectory, std::string filename);
    ~ConfigurationHandler();

	// Getters
	std::string getFilename();
	std::string getDirectory();
	int getMode();

	// enums -- To Refactor Out
	enum mode { MODE_WRITE, MODE_READ };

	// Initialize the ArduinoReadableFileWriter object with the SPAs declared in the JSON
	void initializeAnalyzer(ArduinoReadableFileWriter& arf);

private:
	// Load in the configuration JSON at specified file path
	void loadConfigurationFile(std::string configurationFilePath);

	// Private Variables
	mode arfwriterMode;
	Json::Value decodedJSON;
	std::string workingDirectory;
};