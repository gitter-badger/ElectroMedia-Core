#include "stdafx.h"

#ifndef EMC_ConfigurationFileFields_H_
#define EMC_ConfigurationFileFields_H_

enum class ConfigurationFileFields
{
	Decode,
	Read
};

enum class Endianness
{
	BigEndian,
	LittleEndian,
	Either
};

#endif