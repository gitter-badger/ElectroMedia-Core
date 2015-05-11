#include "stdafx.h"
#include "Constants.h"
#include "ArduinoReadableFileWriter.h"

// ArduinoReadableFileWriter Constructor
// ---
// Initialize our Arduino-Readable-file stream
ArduinoReadableFileWriter::ArduinoReadableFileWriter(char nameOfARF[])
    : arfStream(nameOfARF), mode_(MODE_ARDUINO), numberOfOutputs_(-1), numberOfFrequencyRanges_(0), loopNumber_(0)
{
    frequencyRanges_.reserve(MAXIMUM_NUMBER_OF_FREQUENCY_RANGES);
}

// ArduinoReadableFileWriter Destructor
// ---
// If we have stuff to dealloc, do it here
ArduinoReadableFileWriter::~ArduinoReadableFileWriter()
{
    // For safety, check to see if the user closed the stream. If not, close it
    if(arfStream.is_open())
        Close();

    frequencyRanges_.clear();
}

// bool = addFrequencyRange(double,double,int)
// ---
// Adds a frequency range to our dynamic array of Frequency Ranges. Will return
// true if addition was successful.
bool ArduinoReadableFileWriter::AddFrequencyRange(double lowerFrequency, double upperFrequency, int adjustment, Analyzer& processor)
{
    // If we have an available frequencyRange_, initialize its bounds, add it, and then set its processor
    if(numberOfFrequencyRanges_ < MAXIMUM_NUMBER_OF_FREQUENCY_RANGES)
    {
        AddAndInitializeFrequencyBound(lowerFrequency,upperFrequency,adjustment,processor);
        return true;
    }

    return false;
}

void ArduinoReadableFileWriter::AddAndInitializeFrequencyBound(double lowerFrequency, double upperFrequency, int adjustment, Analyzer& processor)
{
    auto newFreq = new FrequencyRangeProfile();
    newFreq->initializeFrequencyBounds(lowerFrequency, upperFrequency, adjustment);
    newFreq->setProcessor(processor);
    frequencyRanges_.push_back(*newFreq);
}

// setMode(int)	
// ---
// Change the way that the write() function behaves
void ArduinoReadableFileWriter::SetMode(int newMode)
{
    mode_ = newMode;

    switch(mode_)
    {
    case(MODE_ARDUINO):
        numberOfOutputs_ = ARDUINO_UNO_IO_PINS;
        break;

    case(MODE_ARDUINO_MEGA):
        numberOfOutputs_ = ARDUINO_MEGA_IO_PINS - NUMBER_OF_PINS_DEDICATED_TO_LCD;
        break;

    default:
        numberOfOutputs_ = 0;
    }
}

// bool = isTextWritable()
// ---
// Checks to see that the arfStream is open and that mode_ == MODE_TEXT.
bool ArduinoReadableFileWriter::IsTextWritable()
{
    if(!arfStream.is_open())
    {
        CoreMath::Debug("arfStream is not initialized -- cannot write strings to an unopen file!");
        return false;
    }

    if(mode_ != MODE_TEXT)
    {
        CoreMath::Debug("arfStream cannot write a string while not in Text Mode!");
        return false;
    }

    return true;
}

// write(std::string)
// ---
// Writes a single line of text to the output file if and only if the mode is set to
// MODE_TEXT. This function is ignored when writing a *.arf
void ArduinoReadableFileWriter::Write(std::string stringToWrite)
{
    if(IsTextWritable())
    {
        ArduinoReadableFileWriter::arfStream << stringToWrite.c_str() << "\n";
    }
}

// write(int)
// ---
// Writes a single line of text to the output file if and only if the mode is set to
// MODE_TEXT. This function is ignored when writing a *.arf
void ArduinoReadableFileWriter::Write(int intToWrite)
{
    if(IsTextWritable())
    {
        ArduinoReadableFileWriter::arfStream << intToWrite << "\n";
    }
}

// write(double*)
// ---
// Deciphers the data and transforms it into byte format; writes bytes to the output file
// [WIP]
void ArduinoReadableFileWriter::Write(DataSet& dataToWrite)
{
    if(!arfStream.is_open())
    {
        CoreMath::Debug("arfStream is not initialized -- cannot write data to an unopen file!");
        return;
    }

    switch(mode_)
    {
        // Text mode is meant to be human-readable and is used for debug purposes
    case(MODE_TEXT):
        WriteDoubleInTextMode(dataToWrite);
        break;

        // Regular Arduino Mode uses 16 output pins
    case(MODE_ARDUINO):
        break;

        // Arduino MEGA Mode uses 54 output pins, 8 of which are dedicated to an LCD screen
    case(MODE_ARDUINO_MEGA):
        break;

    default:
        CoreMath::Debug("ArduinoReadableFileWriter writer cannot write as it is in an undefined mode!");
    }
}

int ArduinoReadableFileWriter::CalculateDynamicNoiseFloor(DataSet& data)
{
    auto preNFMaximum_ = *std::max_element(data->begin(), data->end());

    return int(preNFMaximum_ * (double(NOISE_FLOOR_PCT) / 100));
}

void ArduinoReadableFileWriter::WriteDoubleInTextMode(DataSet& dataToWrite)
{
    int dynamicNoiseFloor = NOISE_FLOOR;

    for (vector<FrequencyRangeProfile>::iterator it = frequencyRanges_.begin(); it != frequencyRanges_.end(); it++)
    {
        vector<double> dataSubvector(dataToWrite->begin(), dataToWrite->end());
        UniqueDataSet conversionDuplicate = std::make_unique<vector<double>>(dataSubvector);
        auto outputString = (it->convertToBits(conversionDuplicate, dynamicNoiseFloor));

        ArduinoReadableFileWriter::arfStream << outputString;
    }
    ArduinoReadableFileWriter::arfStream << "\n";
}



// close()
// ---
// Close the output file. Not a destructor!
void ArduinoReadableFileWriter::Close()
{
    ArduinoReadableFileWriter::arfStream.close();
}