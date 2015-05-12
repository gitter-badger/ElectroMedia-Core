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

private:
	void Decode();
	void Read();

	ConfigurationHandler& _configHandler;
	vector<boost::shared_ptr<Analyzer> >* _analyzers;
};