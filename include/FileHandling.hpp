#ifndef FileHandling_hpp
#define FileHandling_hpp

#define APP_FILES "../app/"
#define ASSETS "../app/ASSETS"

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
        std::vector<std::string> files;
        public:
            std::unordered_map<string,string> fm;
            std::unordered_map<string,std::vector<char>> im;
            FileHandling();
            void ReadFiles();
            std::string ReadFile(const std::string& file_path);
            std::vector<char> ReadImage(const std::string& file_path);
    };
}

#endif