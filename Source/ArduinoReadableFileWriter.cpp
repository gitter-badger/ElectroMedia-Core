#include "stdafx.h"
#include "ArduinoReadableFileWriter.h"

// ArduinoReadableFileWriter Constructor
// ---
// Initialize our Arduino-Readable-file stream
ArduinoReadableFileWriter::ArduinoReadableFileWriter(char nameOfARF[])
    : arfStream(nameOfARF), mode_(EMC_Output_Mode::Text), numberOfOutputs_(-1)
{
}

// ArduinoReadableFileWriter Destructor
// ---
// If we have stuff to dealloc, do it here
ArduinoReadableFileWriter::~ArduinoReadableFileWriter()
{
    // For safety, check to see if the user closed the stream. If not, close it
    if(arfStream.is_open())
        Close();
}

// setMode(int)	
// ---
// Change the way that the write() function behaves
void ArduinoReadableFileWriter::SetMode(EMC_Output_Mode newMode)
{
    mode_ = newMode;

    switch(mode_)
    {
	case(EMC_Output_Mode::ArduinoReadableFile):
        numberOfOutputs_ = ARDUINO_UNO_IO_PINS;
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

    if(mode_ != EMC_Output_Mode::Text)
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
	case(EMC_Output_Mode::Text):
        WriteDoubleInTextMode(dataToWrite);
        break;

        // Regular Arduino Mode uses 16 output pins
	case(EMC_Output_Mode::ArduinoReadableFile):
        break;

	case(EMC_Output_Mode::Binary):
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
    auto dynamicNoiseFloor = NOISE_FLOOR;

		// TODO

    ArduinoReadableFileWriter::arfStream << "\n";
}



// close()
// ---
// Close the output file. Not a destructor!
void ArduinoReadableFileWriter::Close()
{
    ArduinoReadableFileWriter::arfStream.close();
}