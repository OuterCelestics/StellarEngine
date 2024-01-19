#include "config_loader.h"

namespace Engine {
	ConfigLoader::ConfigLoader(std::string folder, std::string file_name)
		: folder(folder), file_path(folder + "/" + file_name)
	{
		if (!std::filesystem::exists(folder)) {
			if (!std::filesystem::create_directory(folder)) {
				std::cout << "Error creating folder: " << folder << std::endl;
			}
			createConfig(file_path);
		}
		else {
			createConfig(file_path);		
		}
	}

	bool ConfigLoader::writeConfig(const std::map<std::string, std::map<std::string, std::string>>& configData)
    {
		config_file.open(file_path, std::ios::out | std::ios::app);  // Open file in append mode
		if (!config_file.is_open()) {
			std::cout << "Error opening file: " << file_path << std::endl;
			return false;
		}

		// Iterate through categories and key-value pairs and write to the file
		for (const auto& category : configData) {
			config_file << "[" << category.first << "]" << std::endl;
			for (const auto& kvp : category.second) {
				config_file << kvp.first << "=" << kvp.second << std::endl;
			}
			config_file << std::endl; // Add a blank line after each category
		}

		// Close the file
		config_file.close();
		return true;
    }

	bool ConfigLoader::loadConfig(std::string file_path)
	{
		config_file.open(file_path);
		if (!config_file.is_open()) {
			std::cout << "Error opening file: " << file_path << std::endl;
			return false;
		}
		return true;
	}

	bool ConfigLoader::createConfig(std::string file_path)
	{
		config_file.open(file_path);
		std::ifstream template_file("config/default/config_template.txt");
		if (!template_file.is_open()) {
			std::cout << "Error opening template file: template.txt" << std::endl;
			config_file.close();
			return false;
		}

		// Read the content from the template file
		std::stringstream template_content;
		template_content << template_file.rdbuf();

		// Write the template content to the new config file
		config_file << template_content.str();

		// Close both files
		template_file.close();

		// Write default configuration to the file if needed
		config_file.close();

		return true;
	}
}
