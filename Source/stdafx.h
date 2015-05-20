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
#include "EmcSettings.h"
#include "boost\dynamic_bitset\dynamic_bitset.hpp"
#include "boost\function\function0.hpp"

// ENUMS
const enum adjustmentType { ADJUSTMENT_TYPE_CHANGE_UPPER, ADJUSTMENT_TYPE_CHANGE_LOWER, ADJUSTMENT_TYPE_CENTER };

// NAMESPACES
using std::vector;
using boost::dynamic_bitset;

// TYPE DEFINITIONS
typedef std::shared_ptr<vector<char>> AudioFileData;
typedef std::unique_ptr<vector<double>> UniqueDataSet;
typedef std::shared_ptr<vector<double>> DataSet;
typedef vector<double>::iterator DataSetIterator;