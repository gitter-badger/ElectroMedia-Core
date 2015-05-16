#include "stdafx.h"
#include "FFmpegReturnValues.h"

// HEADER file for all MP3 decoding operations
// Scope of this file includes loading/decoding MP3 files and writing decoded MP3 data

// The Decoder uses FFMPEG, an Open-Source Library available via GPL.

FFmpegReturnValue decodeMusic(std::string directoryName, std::string songName);