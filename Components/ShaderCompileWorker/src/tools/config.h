#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>

class Config
{
public:
    Config(std::string folder, std::string file_name);
	bool m_ParseConfig();
    int GetInteger(const std::string section, const std::string key) const;

private:
    std::string trim(const std::string& str);

public:
    std::string folder;
    const std::string file_path;
    std::ofstream config_file;
    mutable std::map<std::string, std::map<std::string, std::string>> configData;
};

