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
	ConfigurationHandler(std::string configurationFileName);
    ~ConfigurationHandler();
	std::string getFilename();
	void initializeSignalProcessingAlgorithms(ArduinoReadableFileWriter& arf);
	int getMode();

	enum mode { MODE_WRITE, MODE_READ };

private:
	void loadConfigurationFile(std::string configurationFileName);

	mode arfwriterMode;
	Json::Value decodedJSON;
};