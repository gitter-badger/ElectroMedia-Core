#include "stdafx.h"
#include "FrequencyRangeProfile.h"

class ArduinoReadableFileWriter
{
public:
    // Constructors / Destructors
    ArduinoReadableFileWriter(char nameOfARF[]);
    ~ArduinoReadableFileWriter();

    // Add a FrequencyRangeProfile with specified characteristics; will probabyl be rewritten such
    // that the user only needs to add the processor and everything else is added automatically
    bool addFrequencyRange(double lowerFrequency, double upperFrequency, int adjustment, SignalProcessingAlgorithm* processor);

    // Sets the mode of the ARFWriter (Text or Byte) according to the enum writeMode
    void setMode(int newMode);

    // Overloaded write options; only double* variant is used to write legitimate ARFs
    void write(std::string stringToWrite);
    void write(int intToWrite);
    void write(dataSet& dataToWrite);
    void close();

    // Enumerated Lists
    static const enum writeMode {MODE_TEXT, MODE_ARDUINO, MODE_ARDUINO_MEGA};

private:
    // Internal function for dealing with whether or not to write as BYTE or std::string
    bool isTextWritable();
    void addAndInitializeFrequencyBound(double lowerFrequency, double upperFrequency, int adjustment, SignalProcessingAlgorithm* processor);
    void writeDoubleInTextMode(dataSet& dataToWrite);

    // Private variables
    std::ofstream arfStream;
    int mode_, numberOfOutputs_;
    size_t numberOfFrequencyRanges_;
    FrequencyRangeProfile* frequencyRanges_;
};