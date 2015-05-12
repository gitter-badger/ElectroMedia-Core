#include "stdafx.h"
#include "EMCModes.h"
#include "FrequencyRangeProfile.h"

class ArduinoReadableFileWriter
{
public:
    // Constructors / Destructors
    ArduinoReadableFileWriter(char nameOfARF[]);
    ~ArduinoReadableFileWriter();

    // Add a FrequencyRangeProfile with specified characteristics; will probabyl be rewritten such
    // that the user only needs to add the processor and everything else is added automatically
    bool AddFrequencyRange(double lowerFrequency, double upperFrequency, int adjustment, Analyzer& processor);

    // Sets the mode of the ARFWriter (Text or Byte) according to the enum writeMode
    void SetMode(EMC_Output_Mode newMode);

    // Overloaded write options; only double* variant is used to write legitimate ARFs
    void Write(std::string stringToWrite);
    void Write(int intToWrite);
    void Write(DataSet& dataToWrite);
    void Close();

private:
    // Internal function for dealing with whether or not to write as BYTE or std::string
    bool IsTextWritable();
    void AddAndInitializeFrequencyBound(double lowerFrequency, double upperFrequency, int adjustment, Analyzer& processor);
    void WriteDoubleInTextMode(DataSet& dataToWrite);
    int CalculateDynamicNoiseFloor(DataSet& data);

    // Private variables
    std::ofstream arfStream;
	EMC_Output_Mode mode_;
	int numberOfOutputs_, dynamicNoiseFloor, loopNumber_;
    size_t numberOfFrequencyRanges_;
    vector<FrequencyRangeProfile> frequencyRanges_;
};