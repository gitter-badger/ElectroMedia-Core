#include "stdafx.h"

#ifndef EMC_EMCModes_H_
#define EMC_EMCModes_H_

enum class EMC_Mode
{ 
	Decode,
	Read
};

enum class EMC_Output_Mode
{
	Text,
	Binary,
	ArduinoReadableFile
};

#endif