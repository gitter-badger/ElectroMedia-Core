#include "stdafx.h"
#include "ConfigurationHandler.h"
#include "CoreMath.h"
#include "MusicFileOperations.h"

// Need cleanup functions!

class EmcCore
{
public:
	EmcCore(std::string configurationFilePath);
	~EmcCore();

	void Run();
	void StartAnalyses();
	void AddAnalyzer(Analyzer* analyzer);

protected:
	void Decode();
	void Read();

private:
	

	ConfigurationHandler& _configHandler;
	vector<std::shared_ptr<Analyzer*> >* _analyzers;
};