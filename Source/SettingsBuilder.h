#include "stdafx.h"
#include "ArduinoReadableFileWriter.h"
#include "EMCModes.h"
#include "EmcSettings.h"
#include "AnalyzerFactory.h"
#include "Dependencies\json\json.h"

#ifndef EMC_SettingsBuilder_H_
#define EMC_SettingsBuilder_H_

class SettingsBuilder
{
public:
    // Constructors / Destructors
	SettingsBuilder(std::string configuration_file_directory, std::string configuration_file_name);
    ~SettingsBuilder();

	void Load();
	EMC_Mode GetMode();

	vector< std::shared_ptr<Analyzer*> >* GetAnalyzers();

private:
	// Load in the configuration JSON at specified file path
	void LoadConfigurationFile(std::string configuration_file_directory, std::string configuration_file_name);
	void HashConfigField(std::string field);
	
	AnalyzerFactory analyzer_factory_;

	std::string configuration_directory_, configuration_filename_;
};

#endif