#include "stdafx.h"
#include "SettingsBuilder.h"

SettingsBuilder::SettingsBuilder(std::string configuration_file_directory, std::string configuration_file_name)
	: configuration_directory_(configuration_file_directory),
	configuration_filename_(configuration_file_name)
{
}

// Load in the JSON Configuration file at the specified path
EmcSettings* SettingsBuilder::Create()
{	
	auto settings = new EmcSettings();

	std::ifstream in(configuration_directory_ + configuration_filename_);
	Json::Reader reader;
	Json::Value decoded_json;
	reader.parse(in, decoded_json);

	// Default to Read Mode
	settings->emc_mode_ = EMC_Mode::Read;

	// TODO: Refactor
	if (decoded_json["mode"].asString().compare("write") == 0)
	{
		settings->emc_mode_ = EMC_Mode::Decode;
	}

	return settings;
}

void SettingsBuilder::HashConfigField(std::string field)
{
	// TODO
}

vector< std::shared_ptr<Analyzer*> >* SettingsBuilder::GetAnalyzers()
{
	vector < std::shared_ptr<Analyzer*> > analyzers;

	//auto it = decoded_json_["Analyzers"].begin();
	//
	//// Each loop corresponds to a subnode in the "algorithms" node
	//while (it != decoded_json_["Analyzers"].end())
	//{
	////	analyzers.push_back(std::make_shared<Analyzer*>( _analyzerFactory.Create((*it)["type"].asString()) ));
	//	std::string something;
	//}
	//
	return &analyzers;
}