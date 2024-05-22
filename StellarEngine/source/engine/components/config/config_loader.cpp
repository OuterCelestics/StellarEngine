#include <iostream>
#include "config_loader.h"

namespace Engine {
	ConfigLoader::ConfigLoader(std::string folder, std::string file_name) : folder(folder), file_path(folder + "/" + file_name) 
	{
		// Load the config file
		if (!m_ParseConfig())
		{
			std::cerr << "Error loading config file: " << file_path << std::endl;
		}
		else
		{
			std::cout << "Config file loaded successfully: " << file_path << std::endl;
		}
	}

	int ConfigLoader::GetInteger(const std::string section, const std::string key) const 
	{
		auto sectionIter = configData.find(section);
		if (sectionIter != configData.end()) 
		{
			auto keyIter = sectionIter->second.find(key);
			if (keyIter != sectionIter->second.end()) 
			{
				return std::stoi(keyIter->second);
			}
			else 
			{
				std::cerr << "Key not found: " << key << " in section: " << section << std::endl;
			}
		} 
		else {
			std::cerr << "Section not found: " << section << std::endl;
		}
		return 0; // Return an empty string if the key or section is not found
	}
	float ConfigLoader::GetFloat(const std::string section, const std::string key) const
	{
		auto sectionIter = configData.find(section);
		if (sectionIter != configData.end())
		{
			auto keyIter = sectionIter->second.find(key);
			if (keyIter != sectionIter->second.end())
			{
				return std::stof(keyIter->second);
			}
			else
			{
				std::cerr << "Key not found: " << key << " in section: " << section << std::endl;
			}
		}
		else
		{
			std::cerr << "Section not found: " << section << std::endl;
		}
		return 0; // Return an empty string if the key or section is not found
	}
	std::string ConfigLoader::getString(const std::string section, const std::string key) const
	{
		auto sectionIter = configData.find(section);
		if (sectionIter != configData.end()) 
		{
			auto keyIter = sectionIter->second.find(key);
			if (keyIter != sectionIter->second.end()) 
			{
				return keyIter->second;
			}
			else 
			{
				std::cerr << "Key not found: " << key << " in section: " << section << std::endl;
			}
		}
		else 
		{
			std::cerr << "Section not found: " << section << std::endl;
		}
		return ""; // Return an empty string if the key or section is not found
	}

	void ConfigLoader::SetInt(const std::string section, const std::string key, int value) const
	{
			// Update configData map with the new value
			configData[section][key] = std::to_string(value);

			// Open the config file for writing
			std::ofstream configFile(file_path);

			// Check if the file is opened successfully
			if (!configFile.is_open())
			{
				// Handle error
				std::cerr << "Error: Unable to open config file for writing\n";
				return;
			}

			// Write the updated configData to the file
			for (const auto& category : configData)
			{
				configFile << "[" << category.first << "]" << std::endl;
				for (const auto& kvp : category.second)
				{
					configFile << kvp.first << "=" << kvp.second << std::endl;
				}
			}

			// Close the file
			configFile.close();
	}

	void ConfigLoader::SetFloat(const std::string section, const std::string key, float value) const
	{
		// Update configData map with the new value
		configData[section][key] = std::to_string(value);

		// Open the config file for writing
		std::ofstream configFile(file_path);

		// Check if the file is opened successfully
		if (!configFile.is_open())
		{
			// Handle error
			std::cerr << "Error: Unable to open config file for writing\n";
			return;
		}

		// Write the updated configData to the file
		for (const auto& category : configData)
		{
			configFile << "[" << category.first << "]" << std::endl;
			for (const auto& kvp : category.second)
			{
				configFile << kvp.first << "=" << kvp.second << std::endl;
			}
		}

		// Close the file
		configFile.close();
	}

	void ConfigLoader::SetString(const std::string section, const std::string key, const std::string value) const
	{
		// Update configData map with the new value
		configData[section][key] = value;

		// Open the config file for writing
		std::ofstream configFile(file_path);

		// Check if the file is opened successfully
		if (!configFile.is_open())
		{
			// Handle error
			std::cerr << "Error: Unable to open config file for writing\n";
			return;
		}

		// Write the updated configData to the file
		for (const auto& category : configData)
		{
			configFile << "[" << category.first << "]" << std::endl;
			for (const auto& kvp : category.second)
			{
				configFile << kvp.first << "=" << kvp.second << std::endl;
			}
		}

		// Close the file
		configFile.close();
	}

	bool ConfigLoader::m_ParseConfig()
{	
		config_file.open(file_path);  // Open the file
	if (!config_file.is_open()) 
	{
		std::cout << "Error opening file: " << file_path << std::endl;
		return false;
	}

	std::string currentSection = "";
	std::string line;
	
	try
	{
		while (std::getline(config_file, line))
		{
			// Remove leading and trailing whitespaces
			line = trim(line);

			// Skip empty lines
			if (line.empty()) {
				continue;
			}

			// Skip comments
			if (line[0] == ';') {
				continue;
			}

			// Check for section header
			if (line[0] == '[' && line.back() == ']') 
			{
				currentSection = line.substr(1, line.size() - 2);
			}
			else 
			{
				// Parse key-value pairs
				std::size_t equalsPos = line.find('=');
				if (equalsPos != std::string::npos) {
					std::string key = trim(line.substr(0, equalsPos));
					std::string value = trim(line.substr(equalsPos + 1));
					configData[currentSection][key] = value;
				}
			}
		}

		config_file.close();  // Close the file explicitly
		return true;
	}
	catch (const std::exception&)
	{
		std::cout << "Error parsing config file: " << file_path + "\n" << std::endl;
	}

	return true;
}


	std::string ConfigLoader::trim(const std::string& str) 
	{
		std::size_t first = str.find_first_not_of(" \t");
		std::size_t last = str.find_last_not_of(" \t");
		return str.substr(first, (last - first + 1));
	}
}
