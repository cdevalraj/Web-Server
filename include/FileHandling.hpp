#ifndef FileHandling_hpp
#define FileHandling_hpp

#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
namespace fs = std::filesystem;

namespace webs
{
    class FileHandling
    {
        public:
            // std::vector<std::string> projects;
            // std::unordered_map<std::string,std::vector<std::string>> projectfiles;
            std::vector<std::string> files;
            FileHandling();
            std::string ReadFile(const std::string& file_path);
            std::vector<char> ReadImage(const std::string& file_path);
            std::unordered_map<std::string, std::string> parseJsonFile(const std::string& filePath);
            bool isImageFile(std::string file);
            bool isAssetFile(std::string file);
    };
}

#endif