#include "stdafx.h"
#include "SettingsBuilder.h"
#include "CoreMath.h"
#include "MusicFileOperations.h"
#include <algorithm>
#include <thread>

#ifndef EMC_EmcCore_H_
#define EMC_EmcCore_H_

class EmcCore
{
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
	SettingsBuilder::AnalyzerCollection* analyzer_collection_;
};

#endif