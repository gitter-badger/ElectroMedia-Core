// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <bitset>
#include <memory>
#include <algorithm>
#include "boost\dynamic_bitset\dynamic_bitset.hpp"
#include "CommonOperations.h"

// ENUMS
const enum adjustmentType { ADJUSTMENT_TYPE_CHANGE_UPPER, ADJUSTMENT_TYPE_CHANGE_LOWER, ADJUSTMENT_TYPE_CENTER };
const enum emcMode { CONVERSION_MODE, VISUALIZE_MODE };

// CONSTANT FLAGS
const bool DEBUG_ENABLED = true;
const bool OUTPUT_IS_BIG_ENDIAN = true;

// CONSTANTS
const int EMC_MODE = CONVERSION_MODE;
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

// NAMESPACES
using std::cout;
using std::vector;
using boost::dynamic_bitset;

// TYPE DEFINITIONS
typedef std::shared_ptr<vector<char>> AudioFileData;
typedef std::unique_ptr<vector<double>> UniqueDataSet;
typedef std::shared_ptr<vector<double>> DataSet;
typedef vector<double>::iterator DataSetIterator;