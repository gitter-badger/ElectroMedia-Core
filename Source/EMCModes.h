#include "stdafx.h"

#ifndef EMCModesDefinition
#define EMCModesDefinition

enum EMC_Mode
{ 
	Decode,
	Read
};

enum EMC_Output_Mode
{
	Text,
	Binary,
	ArduinoReadableFile
};

#endif