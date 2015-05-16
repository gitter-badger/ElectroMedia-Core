#include "stdafx.h"
#include "ConfigurationHandler.h"

ConfigurationHandler::ConfigurationHandler(std::string configuration_file_directory, std::string configuration_file_name)
	: arfwriter_mode_(EMC_Mode::Read),
	configuration_directory_(configuration_file_directory),
	configuration_filename_(configuration_file_name)
{
	decoded_json_ = new Json::Value();
	LoadConfigurationFile(configuration_file_directory + configuration_file_name);
}

// Load in the JSON Configuration file at the specified path
void ConfigurationHandler::LoadConfigurationFile(std::string configuration_file_path)
{	
	std::ifstream in(configuration_file_path);
	Json::Reader reader;
	reader.parse(in, decoded_json_);

	// Default to Read Mode
	arfwriter_mode_ = EMC_Mode::Read;

	// TODO: Refactor
	if (decoded_json_["mode"].asString().compare("write") == 0)
	{
		arfwriter_mode_ = EMC_Mode::Decode;
	}
}

void ConfigurationHandler::HashConfigField(std::string field)
{
	// TODO
}

EMC_Mode ConfigurationHandler::GetMode()
{
	return arfwriter_mode_;
}

// Returns the filename of the song in the configuration file
std::string ConfigurationHandler::GetFilename()
{
	return decoded_json_["filename"].asString();
}

// Returns the file path of the working directory
std::string ConfigurationHandler::GetDirectory()
{
	return configuration_directory_;
}

std::string ConfigurationHandler::GetFullPath()
{
	return ConfigurationHandler::GetDirectory() + ConfigurationHandler::GetFilename();
}


vector< std::shared_ptr<Analyzer*> >* ConfigurationHandler::GetAnalyzers()
{
	vector < std::shared_ptr<Analyzer*> > analyzers;

	auto it = decoded_json_["Analyzers"].begin();
	
	// Each loop corresponds to a subnode in the "algorithms" node
	while (it != decoded_json_["Analyzers"].end())
	{
	//	analyzers.push_back(std::make_shared<Analyzer*>( _analyzerFactory.Create((*it)["type"].asString()) ));
		std::string something;
	}

	return &analyzers;
}