#include "stdafx.h"
#include "ConfigurationFileFields.h"
#include "EMCModes.h"

#ifndef EMC_EmcSettings_H_
#define EMC_EmcSettings_H_ 

#define Settings EmcSettings::GetInstance()

class EmcSettings
{
public:
	static EmcSettings& GetInstance()
	{
		static EmcSettings instance;
		return instance;
	}
	EmcSettings() { }
	EmcSettings(EmcSettings const&) = delete;
	void operator=(EmcSettings const&) = delete;

	const std::string kConfigurationFileName = "config.json";
	const std::string kEmcFileExtension = ".emc";
	const std::string kArFileExtension = ".arf";

	const int kSongEndingPaddingSize = 8;
	const double kBoundaryConversionScalar = 10.91;
	const double kBoundaryConversionOffset = 7.33;

	int window_size_ = 8192;
	int window_shift_amount_ = 4096;
	double maximum_frequency_accounted_ = 2000;
	double temporal_shift_width_ = 0.02334;
	double noise_floor_percentage_ = 30.0;
	Endianness endianness_of_output_ = Endianness::BigEndian;
	bool debug_mode_;

	std::string configuration_directory_;
	std::string song_filename_;
	EMC_Mode	emc_mode_;

	void CalculateTemporalShiftWidth()
	{
		temporal_shift_width_ = (double)window_shift_amount_ * 0.01140 / 1000;
	}
};

#endif