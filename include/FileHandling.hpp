#ifndef FileHandling_hpp
#define FileHandling_hpp

#define APP_FILES "./app/"
#define ASSETS "./app/assets/"
#define ENTRY_POINT "index.html"

#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
namespace fs = std::filesystem;

namespace webs
{
    class FileHandling
    {
        std::vector<std::string> appfiles,assetfiles;
        void ReadFiles();
        std::string ReadFile(const std::string& file_path);
        std::vector<char> ReadImage(const std::string& file_path);
        public:
            std::unordered_map<std::string,std::string> fm;
            std::unordered_map<std::string,std::vector<char>> im;
            FileHandling();
            bool isImageFile(std::string file);
    };
}

#endif