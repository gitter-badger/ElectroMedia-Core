#include "stdafx.h"

class EmcSettings
{
public:
	const std::string kConfigurationFileName = "config.json";
	const std::string kEmcFileExtension = ".emc";
	const std::string kArFileExtension = ".arf";

	const int kSongEndingPaddingSize = 8;
	const double kBoundaryConversionScalar = 10.91;
	const double kBoundaryConversionOffset = 7.33;

	enum Endianness
	{
		BigEndian,
		LittleEndian,
		Either
	};

	int window_size_ = 8192;
	int window_shift_amount_ = 4096;
	double maximum_frequency_accounted_ = 2000;
	double temporal_shift_width_ = 0.02334;
	double noise_floor_percentage_ = 30.0;
	Endianness endianness_of_output_ = BigEndian;

	std::string configuration_directory_;
	std::string configuration_filename_;
	EMC_Mode	arfwriter_mode_;

	void CalculateTemporalShiftWidth()
	{
		temporal_shift_width_ = (double)window_shift_amount_ * 0.01140 / 1000;
	}
};