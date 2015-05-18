#include "stdafx.h"
#include "SettingsBuilder.h"

SettingsBuilder::SettingsBuilder(std::string configuration_file_directory, std::string configuration_file_name)
	: arfwriter_mode_(EMC_Mode::Read),
	configuration_directory_(configuration_file_directory),
	configuration_filename_(configuration_file_name)
{
	decoded_json_ = new Json::Value();
	LoadConfigurationFile(configuration_file_directory + configuration_file_name);
}

// Load in the JSON Configuration file at the specified path
void SettingsBuilder::LoadConfigurationFile(std::string configuration_file_path)
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

void SettingsBuilder::HashConfigField(std::string field)
{
	// TODO
}

EMC_Mode SettingsBuilder::GetMode()
{
	return arfwriter_mode_;
}

vector< std::shared_ptr<Analyzer*> >* SettingsBuilder::GetAnalyzers()
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

EmcSettings* SettingsBuilder::Create()
{
	return new EmcSettings();
}