#include "stdafx.h"
#include "ArduinoReadableFileWriter.h"

// ArduinoReadableFileWriter Constructor
// ---
// Initialize our Arduino-Readable-file stream
ArduinoReadableFileWriter::ArduinoReadableFileWriter(char* nameOfARF) 
    : arfStream(nameOfARF), mode_(MODE_ARDUINO), numberOfOutputs_(-1), numberOfFrequencyRanges_(0)
{
    frequencyRanges_ = new FrequencyRangeProfile[MAXIMUM_NUMBER_OF_FREQUENCY_RANGES];

    // This is an example of the various ranges you can set. First two parameters
    // are in Hz and correspond to lower and upper frequency bounds. The third
    // argument is an enumerated option that selects which of the two boundaries
    // are altered for bit-wise optimization
    addFrequencyRange(50,  200,  ADJUSTMENT_TYPE_CHANGE_UPPER, new SignalProcessingAlgorithm());
    addFrequencyRange(200, 400,  ADJUSTMENT_TYPE_CENTER, new SignalProcessingAlgorithm());
    addFrequencyRange(300, 600,  ADJUSTMENT_TYPE_CENTER, new SignalProcessingAlgorithm());
    addFrequencyRange(200, 1000, ADJUSTMENT_TYPE_CHANGE_LOWER, new SPAHillEffect());
}

// ArduinoReadableFileWriter Destructor
// ---
// If we have stuff to dealloc, do it here
ArduinoReadableFileWriter::~ArduinoReadableFileWriter()
{
    // For safety, check to see if the user closed the stream. If not, close it
    if(arfStream.is_open())
        close();

    delete[] frequencyRanges_;
}

// bool = addFrequencyRange(double,double,int)
// ---
// Adds a frequency range to our dynamic array of Frequency Ranges. Will return
// true if addition was successful.
bool ArduinoReadableFileWriter::addFrequencyRange(double lowerFrequency, double upperFrequency, int adjustment, SignalProcessingAlgorithm* processor)
{
    // If we have an available frequencyRange_, initialize its bounds, add it, and then set its processor
    if(numberOfFrequencyRanges_ < MAXIMUM_NUMBER_OF_FREQUENCY_RANGES)
    {
        addAndInitializeFrequencyBound(lowerFrequency,upperFrequency,adjustment,processor);
        return true;
    }

    return false;
}

void ArduinoReadableFileWriter::addAndInitializeFrequencyBound(double lowerFrequency, double upperFrequency, int adjustment, SignalProcessingAlgorithm* processor)
{
    frequencyRanges_[numberOfFrequencyRanges_].initializeFrequencyBounds(lowerFrequency,upperFrequency,adjustment);
    frequencyRanges_[numberOfFrequencyRanges_++].setProcessor(*processor);
}

// setMode(int)	
// ---
// Change the way that the write() function behaves
void ArduinoReadableFileWriter::setMode(int newMode)
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
bool ArduinoReadableFileWriter::isTextWritable()
{
    if(!arfStream.is_open())
    {
        debug("arfStream is not initialized -- cannot write strings to an unopen file!");
        return false;
    }

    if(mode_ != MODE_TEXT)
    {
        debug("arfStream cannot write a string while not in Text Mode!");
        return false;
    }

    return true;
}

// write(std::string)
// ---
// Writes a single line of text to the output file if and only if the mode is set to
// MODE_TEXT. This function is ignored when writing a *.arf
void ArduinoReadableFileWriter::write(std::string stringToWrite)
{
    if(isTextWritable())
    {
        ArduinoReadableFileWriter::arfStream << stringToWrite.c_str() << endl;
    }
}

// write(int)
// ---
// Writes a single line of text to the output file if and only if the mode is set to
// MODE_TEXT. This function is ignored when writing a *.arf
void ArduinoReadableFileWriter::write(int intToWrite)
{
    if(isTextWritable())
    {
        ArduinoReadableFileWriter::arfStream << intToWrite << endl;
    }
}

// write(double*)
// ---
// Deciphers the data and transforms it into byte format; writes bytes to the output file
// [WIP]
void ArduinoReadableFileWriter::write(double* dataToWrite)
{
    if(!arfStream.is_open())
    {
        debug("arfStream is not initialized -- cannot write data to an unopen file!");
        return;
    }

    switch(mode_)
    {
        // Text mode is meant to be human-readable and is used for debug purposes
    case(MODE_TEXT):
        writeDoubleInTextMode(dataToWrite);
        break;

        // Regular Arduino Mode uses 16 output pins
    case(MODE_ARDUINO):
        break;

        // Arduino MEGA Mode uses 54 output pins, 8 of which are dedicated to an LCD screen
    case(MODE_ARDUINO_MEGA):
        break;

    default:
        debug("ArduinoReadableFileWriter writer cannot write as it is in an undefined mode!");
    }
}

void ArduinoReadableFileWriter::writeDoubleInTextMode(double* dataToWrite)
{
    auto dynamicNoiseFloor = calculateDynamicNoiseFloor(dataToWrite,0,200);

    for(int i=0; i<numberOfFrequencyRanges_; i++)
    {
        auto outputString = (frequencyRanges_[i].convertToBits(dataToWrite, dynamicNoiseFloor));
        ArduinoReadableFileWriter::arfStream << outputString << ".";
    }
    ArduinoReadableFileWriter::arfStream << "\n";
}

// close()
// ---
// Close the output file. Not a destructor!
void ArduinoReadableFileWriter::close()
{
    ArduinoReadableFileWriter::arfStream.close();
}