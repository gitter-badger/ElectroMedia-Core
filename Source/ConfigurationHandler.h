#include "stdafx.h"
#include "ArduinoReadableFileWriter.h"
#include "EMCModes.h"
#include "AnalyzerFactory.h"
#include "Dependencies\json\json.h"

#ifndef EMC_ConfigurationHandler_H_
#define EMC_ConfigurationHandler_H_

class ConfigurationHandler
{
public:
    // Constructors / Destructors
	ConfigurationHandler(std::string configuration_file_directory, std::string configuration_file_name);
    ~ConfigurationHandler();

	// Getters
	std::string GetFilename();
	std::string GetDirectory();
	std::string GetFullPath();
	EMC_Mode GetMode();

	vector< std::shared_ptr<Analyzer*> >* GetAnalyzers();

private:
	// Load in the configuration JSON at specified file path
	void LoadConfigurationFile(std::string configuration_file_path);
	void HashConfigField(std::string field);
	
	// Private Variables
	EMC_Mode	arfwriter_mode_;
	Json::Value decoded_json_;
	
	// PostRefactor
	std::string configuration_directory_;
	std::string configuration_filename_;

	AnalyzerFactory analyzer_factory_;
};

#endif