#include "stdafx.h"
#include "ArduinoReadableFileWriter.h"
#include "json.h"

/* 
 * NEW FILE -- In the process of being designed!
 */


class ConfigurationHandler
{
public:
    // Constructors / Destructors
	ConfigurationHandler();
    ~ConfigurationHandler();
	void loadConfigurationFile(std::string configurationFileName);
    void addDefinition(std::string key, std::string value); // Adds an entry to the .esf if it doesn't already exist
	void setArduinoReadableFileWriter(ArduinoReadableFileWriter& arf);
	std::string getFilename();
	void initializeSignalProcessingAlgorithms(ArduinoReadableFileWriter& arf);
	void generateDefault();

private:
	std::string configurationFilename;
};