#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>

namespace Engine {
    class ConfigLoader {
    public:
        ConfigLoader(std::string folder, std::string file_name);
        bool writeConfig(const std::map<std::string, std::map<std::string, std::string>>& configData);
        bool loadConfig();
        int getInteger(const std::string& section, const std::string& key) const;
        std::string getString(const std::string& section, const std::string& key) const;

    private:
        bool parseConfig();
        std::string folder;
        std::string file_path;
        std::ofstream config_file;
        std::map<std::string, std::map<std::string, std::string>> configData;

        // Helper function to remove leading and trailing whitespaces from a string
        static std::string trim(const std::string& str);
    };
}

#endif // CONFIG_LOADER_H
