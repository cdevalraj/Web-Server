#include "../include/FileHandling.hpp"

webs::FileHandling::FileHandling()
{
    std::string folder_path1 = "../app/",folder_path2 = "../app/assets";
    try
    {
        for(const auto &entry : fs::directory_iterator(folder_path1))
        {
            fs::path file_path=entry.path();
            std::string file=file_path.filename().string();
            files.push_back(file);
        }
        for(const auto &entry : fs::directory_iterator(folder_path2))
        {
            fs::path file_path=entry.path();
            std::string file=file_path.filename().string();
            files.push_back(file);
        }
    }
    catch(fs::filesystem_error &e)
    {
        std::cerr<<"Error: "<<e.what()<<std::endl;
    }
    ReadFiles();
}

void webs::FileHandling::ReadFiles()
{
    for(std::string file:files)
    {
        if(file.find('.jpg')!=std::string::npos)
        {}
        else
        {}
    }
}

std::string webs::FileHandling::ReadFile(const std::string& file_path)
{
    std::ifstream f(file_path, std::ios::in | std::ios::binary);
    if (!f) {
        throw runtime_error("Failed to open file: "+file_path);
    }
    std::stringstream str;
    str<<f.rdbuf();
    return str.str();
}

std::vector<char> webs::FileHandling::ReadImage(const std::string& file_path)
{
    ifstream file(file_path,ios::binary | ios::ate);
    if(!file)
    {
        throw runtime_error("Failed to open file: "+file_path);
    }
    long file_size=file.tellg();
    file.seekg(0,ios::beg);
    vector<char> buffer(file_size);
    if(!file.read(buffer.data(),file_size))
    {
        throw std::runtime_error("Failed to read file: "+file_path);
    }
    return buffer;
}