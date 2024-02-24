#include "config_loader.h"

namespace Engine {
	ConfigLoader::ConfigLoader(std::string folder, std::string file_name)
		: folder(folder), file_path(folder + "/" + file_name)
	{
		m_ParseConfig();
	}

	bool ConfigLoader::WriteConfig(const std::map<std::string, std::map<std::string, std::string>>& configData)
	{
		config_file.open(file_path, std::ios::out | std::ios::app);  // Open file in append mode
		if (!config_file.is_open()) 
		{
			std::cout << "Error opening file: " << file_path << std::endl;
			return false;
		}

		// Iterate through categories and key-value pairs and write to the file
		for (const auto& category : configData) 
		{
			config_file << "[" << category.first << "]" << std::endl;
			for (const auto& kvp : category.second) 
			{
				config_file << kvp.first << "=" << kvp.second << std::endl;
			}
			config_file << std::endl; // Add a blank line after each category
		}

		// Close the file
		config_file.close();
		return true;
	}

	bool ConfigLoader::LoadConfig()
	{
		return m_ParseConfig();
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
		// Open the config file for reading and writing
		std::fstream configFile(file_path, std::ios::in | std::ios::out);

		// Check if the file is opened successfully
		if (!configFile.is_open())
		{
			// Handle error
			std::cerr << "Error: Unable to open config file for writing\n";
			return;
		}

		std::string line;
		std::string currentSection;
		bool sectionFound = false;

		// Iterate through the file to find the section and key
		while (std::getline(configFile, line))
		{
			// Trim leading and trailing whitespaces
			line = trim(line);

			// Check for section header
			if (line.size() > 2 && line.front() == '[' && line.back() == ']')
			{
				currentSection = line.substr(1, line.size() - 2);
				if (currentSection == section)
				{
					sectionFound = true;
				}
			}

			// Check for key-value pairs
			if (sectionFound && line.find(key + "=") != std::string::npos)
			{
				// Update the existing value
				configFile.seekp(configFile.tellg() - line.length() - 1); // Move the cursor back to overwrite
				configFile << key << "=" << value;
				configFile.close();
				return;
			}
		}

		// If section or key not found, append to the end of the file
		if (!sectionFound)
		{
			configFile << "[" << section << "]\n";
		}
		configFile << key << "=" << value << "\n";

		// Close the file
		configFile.close();
	}

	bool ConfigLoader::m_ParseConfig()
	{
		std::ifstream file(file_path);
		if (!file.is_open()) 
		{
			std::cout << "Error opening file: " << file_path << std::endl;
			return false;
		}

		std::string currentSection = "";
		std::string line;
		
		try
		{
			while (std::getline(file, line)) 
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

			file.close();  // Close the file explicitly
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
