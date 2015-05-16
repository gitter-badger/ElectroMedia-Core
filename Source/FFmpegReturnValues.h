#include "stdafx.h"

#ifndef FFmpegReturnValuesDefinition
#define FFmpegReturnValuesDefinition

enum FFmpegReturnValue
{
	Success,
	NoFileFound,
	NoStreamAvailable,
	NoCodec,
	CodecCannotBeOpened,
	NoOutputFileAvailable
};

#endif