#include "../include/Router.hpp"

inline bool file_exists(const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

webs::Router::Router():File_Handler()
{
    /*For a more versatile WebServer*/
    // for(std::string proj:projects)
    // {
    //     for(std::string file:projectfiles[proj])
    //     {
    //         if(isAssetFile(file))
    //         {
    //             if(isImageFile(file))
    //                 Route_images["/"+proj+"/assets/"+file]=ReadImage("./app/"+proj+"/assets/"+file);
    //             else
    //                 Route_files["/"+proj+"/assets/"+file]=ReadFile("./app/"+proj+"/assets/"+file);
    //         }
    //         else
    //         {
    //             if(file==ENTRY_POINT)
    //                 Route_files["/"+proj+"/"]=ReadFile("./app/"+proj+"/"+file);
    //             else
    //                 Route_files["/"+proj+"/"+file]=ReadFile("./app/"+proj+"/"+file);
    //         }
    //     }
    // }
    // for(std::string file:files)
    // {
    //     if(file==ROUTE_CONFIG)
    //     {
    //         RedirectURL=parseJsonFile("./app/rconfig.json");
    //     }
    //     else if(isAssetFile(file))
    //     {
    //         if(isImageFile(file))
    //             Route_images["/assets/"+file]=ReadImage("./app/assets/"+file);
    //         else
    //             Route_files["/assets/"+file]=ReadFile("./app/assets/"+file);
    //     }
    //     else
    //     {
    //         if(file==ENTRY_POINT)
    //             Route_files["/"]=ReadFile("./app/"+file);
    //         else
    //             Route_files["/"+file]=ReadFile("./app/"+file);
    //     }
    // }
    if(file_exists(REROUTE_CONFIG))
    {
        RedirectURL=parseJsonFile(REROUTE_CONFIG);
    }
}

void webs::Router::Route(std::string &path)
{
    
}