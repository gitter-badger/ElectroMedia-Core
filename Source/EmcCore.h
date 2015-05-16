#include "stdafx.h"
#include "ConfigurationHandler.h"
#include "CoreMath.h"
#include "MusicFileOperations.h"
#include <thread>

#ifndef EMC_EmcCore_H_
#define EMC_EmcCore_H_

class EmcCore
{
	const std::string kConfigurationFileName = "config.json";
	typedef vector< std::shared_ptr<Analyzer*> >* AnalyzerCollection;

public:
	EmcCore(std::string configuration_file_path);
	~EmcCore();

	void Run();
	void StartAnalyses();
	void AddAnalyzer(Analyzer* analyzer);

protected:
	void Decode();
	void Read();

private:
	ConfigurationHandler* configuration_handler_;
	AnalyzerCollection analyzer_collection_;
};

#endif