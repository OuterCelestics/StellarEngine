#include "config.h"

Config::Config(std::string folder, std::string file_name)
	: folder(folder), file_path(folder + "/" + file_name)
{
	m_ParseConfig();
}

bool Config::m_ParseConfig()
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

int Config::GetInteger(const std::string section, const std::string key) const
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

std::string Config::trim(const std::string& str)
{
	std::size_t first = str.find_first_not_of(" \t");
	std::size_t last = str.find_last_not_of(" \t");
	return str.substr(first, (last - first + 1));
}

