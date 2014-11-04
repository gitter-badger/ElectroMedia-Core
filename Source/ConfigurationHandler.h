#include "stdafx.h"
#include "ArduinoReadableFileWriter.h"

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

protected:
    void addFrequencyRangeFromConfig(std::string spaString);

private:
    void generateDefault();
    ArduinoReadableFileWriter& arf_;
};