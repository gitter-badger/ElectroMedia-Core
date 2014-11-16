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
    ConfigurationHandler(ArduinoReadableFileWriter& arf);
    ~ConfigurationHandler();
    void loadInConfigurationSettings();
    void addDefinition(std::string key, std::string value); // Adds an entry to the .esf if it doesn't already exist

protected:
    void initializeSignalProcessingAlgorithms(Json::Value root);

private:
    void generateDefault();
    ArduinoReadableFileWriter& arf_;
};