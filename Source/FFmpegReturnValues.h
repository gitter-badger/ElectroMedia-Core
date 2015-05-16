#include "stdafx.h"

#ifndef EMC_FFmpegReturnValues_H_
#define EMC_FFmpegReturnValues_H_

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