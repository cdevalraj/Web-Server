#include "../include/File_Handler.hpp"

webs::File_Handler::File_Handler()
{
    // std::string folder_path1 = "./app",folder_path2 = "./app/assets";
    // try
    // {
        /*This is code will be useful for a more versatile Web_Server like Apache HTTP Server,
           because in that it can handle multiple Projects, i.e. it can serve multiple projects.*/

    //     for(const auto &entry : fs::directory_iterator(folder_path))
    //     {
    //         fs::path file_path=entry.path();
    //         std::string file=file_path.filename().string();
    //         projects.push_back(file);
    //     }
    //     for(std::string proj:projects)
    //     {
    //         bool flag=false;
    //         projectfiles[proj]=std::vector<std::string>();
    //         for(const auto &entry : fs::directory_iterator(folder_path+"/"+proj))
    //         {
    //             fs::path file_path=entry.path();
    //             std::string file=file_path.filename().string();
    //             if(file.find(".")!=std::string::npos)
    //                 projectfiles[proj].push_back(file);
    //             else
    //                 flag=true;
    //         }
    //         if(flag)
    //         {
    //             for(const auto &entry : fs::directory_iterator(folder_path+"/"+proj+"/assets"))
    //             {
    //                 fs::path file_path=entry.path();
    //                 std::string file=file_path.filename().string();
    //                 projectfiles[proj].push_back(file);
    //             }
    //         }
    //     }
    //     for(const auto &entry : fs::directory_iterator(folder_path1))
    //     {
    //         fs::path file_path=entry.path();
    //         std::string file=file_path.filename().string();
    //         if(file!="assets")
    //             files.push_back(file);
    //     }
    //     for(const auto &entry : fs::directory_iterator(folder_path2))
    //     {
    //         fs::path file_path=entry.path();
    //         std::string file=file_path.filename().string();
    //         files.push_back(file);
    //     }
    // }
    // catch(fs::filesystem_error &e)
    // {
    //     std::cerr<<"Error: "<<e.what()<<std::endl;
    // }
}

std::string webs::File_Handler::ReadFile(const std::string& file_path)
{
    std::ifstream f(file_path, std::ios::in | std::ios::binary);
    if (!f) {
        throw std::runtime_error("Failed to open file(ReadFile): "+file_path);
    }
    std::stringstream str;
    str<<f.rdbuf();
    return str.str();
}

std::vector<char> webs::File_Handler::ReadImage(const std::string& file_path)
{
    std::ifstream file(file_path,std::ios::binary | std::ios::ate);
    if(!file)
    {
        throw std::runtime_error("Failed to open file(Readimage): "+file_path);
    }
    long file_size=file.tellg();
    file.seekg(0,std::ios::beg);
    std::vector<char> buffer(file_size);
    if(!file.read(buffer.data(),file_size))
    {
        throw std::runtime_error("Failed to read file: "+file_path);
    }
    return buffer;
}

std::unordered_map<std::string, std::string> webs::File_Handler::parseJsonFile(const std::string& filePath)
{
    std::string jsonString=ReadFile(filePath);

    // Parse the JSON string
    std::unordered_map<std::string,std::string> jsonMap;
    std::string key="",value="",str;
    bool inread=false;
    for(char c:jsonString)
    {
        if(c=='"')
        {
            inread=!inread;
            if(key=="")
            {
                key=str;
                str.clear();
            }
            else
            {
                value=str;
                str.clear();
            }
        }
        else if(c==',' || c=='}')
        {
            jsonMap[key]=value;
            key.clear();
            value.clear();
        }
        else if(inread)
            str+=c;
    }
    return jsonMap;
}

bool webs::File_Handler::isImageFile(std::string file)
{
    return( file.find(".jpg")!=std::string::npos || 
            file.find(".png")!=std::string::npos ||
            file.find(".apng")!=std::string::npos ||
            file.find(".gif")!=std::string::npos ||
            file.find(".webp")!=std::string::npos ||
            file.find(".ico")!=std::string::npos );
}