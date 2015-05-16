#include "stdafx.h"

#ifndef EMC_Constants_H_
#define EMC_Constants_H_

// CONSTANT FLAGS
const bool DEBUG_ENABLED = true;
const bool OUTPUT_IS_BIG_ENDIAN = true;

// CONSTANTS
const int WINDOW_SIZE = 8192;
const int WINDOW_SHIFT_AMOUNT = 4096;
const int SONG_ENDING_PAD = 8;
const int NOISE_FLOOR = 50;
const int NOISE_FLOOR_PCT = 30;
const int NUMBER_OF_PINS_DEDICATED_TO_LCD = 8;
const int MAXIMUM_NUMBER_OF_FREQUENCY_RANGES = 32;

const double TEMPORAL_SHIFT_WIDTH = 0.02334; // WINDOW_SHIFT_AMOUNT * 0.01140 / 1000
const double BOUNDARY_CONVERSION_SCALAR = 10.91;
const double BOUNDARY_CONVERSION_OFFSET = 7.33;
const double PI = 3.1415926;
const double MAXIMUM_FREQUENCY_ACCOUNTED = 2000;

const std::string EMC_FILE_EXTENSION = ".emc";
const std::string AR_FILE_EXTENSION = ".arf";
const std::string CONFIGURATION_FILE_NAME = "config.json";

// ARDUINO SPECIFICS
const int ARDUINO_UNO_IO_PINS = 16;
const int ARDUINO_MEGA_IO_PINS = 54;

#endif