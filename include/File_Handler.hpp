#ifndef File_Handler_hpp
#define File_Handler_hpp


#include "Headers.hpp"

namespace webs
{
    class File_Handler
    {
        public:
            // std::vector<std::string> projects;
            // std::unordered_map<std::string,std::vector<std::string>> projectfiles;
            // std::vector<std::string> files;
            File_Handler();
            std::string ReadFile(const std::string& file_path);
            std::vector<char> ReadImage(const std::string& file_path);
            std::unordered_map<std::string, std::string> parseJsonFile(const std::string& filePath);
            bool isImageFile(std::string file);
    };
}

#endif