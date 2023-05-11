#include "../include/FileHandling.hpp"

webs::FileHandling::FileHandling()
{
    std::string folder_path1 = "./app",folder_path2 = "./app/assets";
    try
    {
        /*This is code will be useful for a more versatile Web_Server like Apache HTTP Server,
           because in that it can handle multiple Projects, i.e. it can serve multiple projects.*/

        // for(const auto &entry : fs::directory_iterator(folder_path))
        // {
        //     fs::path file_path=entry.path();
        //     std::string file=file_path.filename().string();
        //     projects.push_back(file);
        // }
        // for(std::string proj:projects)
        // {
        //     bool flag=false;
        //     projectfiles[proj]=std::vector<std::string>();
        //     for(const auto &entry : fs::directory_iterator(folder_path+"/"+proj))
        //     {
        //         fs::path file_path=entry.path();
        //         std::string file=file_path.filename().string();
        //         if(file.find(".")!=std::string::npos)
        //             projectfiles[proj].push_back(file);
        //         else
        //             flag=true;
        //     }
        //     if(flag)
        //     {
        //         for(const auto &entry : fs::directory_iterator(folder_path+"/"+proj+"/assets"))
        //         {
        //             fs::path file_path=entry.path();
        //             std::string file=file_path.filename().string();
        //             projectfiles[proj].push_back(file);
        //         }
        //     }
        // }
        for(const auto &entry : fs::directory_iterator(folder_path1))
        {
            fs::path file_path=entry.path();
            std::string file=file_path.filename().string();
            if(file!="assets")
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
}

std::string webs::FileHandling::ReadFile(const std::string& file_path)
{
    std::ifstream f(file_path, std::ios::in | std::ios::binary);
    if (!f) {
        throw std::runtime_error("Failed to open file: "+file_path);
    }
    std::stringstream str;
    str<<f.rdbuf();
    return str.str();
}

std::vector<char> webs::FileHandling::ReadImage(const std::string& file_path)
{
    std::ifstream file(file_path,std::ios::binary | std::ios::ate);
    if(!file)
    {
        throw std::runtime_error("Failed to open file: "+file_path);
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

std::unordered_map<std::string, std::string> webs::FileHandling::parseJsonFile(const std::string& filePath)
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

bool webs::FileHandling::isImageFile(std::string file)
{
    return( file.find(".jpg")!=std::string::npos || 
            file.find(".png")!=std::string::npos ||
            file.find(".apng")!=std::string::npos ||
            file.find(".gif")!=std::string::npos ||
            file.find(".webp")!=std::string::npos ||
            file.find(".ico")!=std::string::npos );
}

bool webs::FileHandling::isAssetFile(std::string file)
{
    return( isImageFile(file) ||
            (file.find(".json")==std::string::npos && file.find(".js")!=std::string::npos) || 
            file.find(".css")!=std::string::npos ||
            file.find(".php")!=std::string::npos ||
            file.find(".ts")!=std::string::npos ||
            file.find(".svg")!=std::string::npos );
}

// for(char c:jsonString)
//     {
//         if(c=='"')
//         {
//             if(!inKey)
//                 inKey=true;
//             else if(!inValue)
//                 inValue=true;
//             else
//             {
//                 jsonMap[key]=value;
//                 key.clear();
//                 value.clear();
//                 inKey = true;
//                 inValue = false;
//             }
//         }
//         else if(c==':')
//             inKey=false;
//         else if(c==',' || c=='}')
//         {
//             jsonMap[key] = value;
//             key.clear();
//             value.clear();
//             inKey = true;
//             inValue = false;
//         }
//         else if(inKey)
//             key+=c;
//         else if(inValue)
//             value+=c;
//     }