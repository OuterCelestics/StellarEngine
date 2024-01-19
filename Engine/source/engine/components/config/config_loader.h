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
    private:
        bool loadConfig(std::string file_path);
        bool createConfig(std::string file_path);

        std::string folder;
        std::string file_path;
        std::ofstream config_file;
    };
}

#endif // CONFIG_LOADER_H
