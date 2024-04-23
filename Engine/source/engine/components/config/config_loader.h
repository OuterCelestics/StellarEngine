#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>

namespace Engine {
    class ConfigLoader {
    public:
        ConfigLoader(std::string folder, std::string file_name);

        // Get values
        int GetInteger(const std::string section, const std::string key) const;
        float GetFloat(const std::string section, const std::string key) const;
        std::string getString(const std::string section, const std::string key) const;
        
        // Set values
        void SetInt(const std::string section, const std::string key, int value) const;
        void SetFloat(const std::string section, const std::string key, float value) const;
        void SetString(const std::string section, const std::string key, std::string value) const;
    private:
        bool m_ParseConfig();
        std::string folder;
        const std::string file_path;
        std::ifstream config_file;
        mutable std::map<std::string, std::map<std::string, std::string>> configData;

        // Helper function to remove leading and trailing whitespaces from a string
        static std::string trim(const std::string& str);
    };
}