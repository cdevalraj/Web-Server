#include "../include/Router.hpp"

inline bool file_exists(const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

webs::Router::Router():File_Handler(),Request_Handler(),Response_Handler()
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

void webs::Router::Route(int soc)
{
  std::unordered_map<std::string,std::string> req=handleReq(soc);

  std::string path=APP;
  if(file_exists(APP+req["path"]))
  {
    path+=req["path"];
    Send(soc,path,req["path"]);
  }
  else if(RedirectURL.find(req["path"])!=RedirectURL.end())
  {
    path+=RedirectURL[req["path"]];
    Send(soc,path,RedirectURL[req["path"]]);
  }
  else if(RedirectURL.find("/*")!=RedirectURL.end())
  {
    path+=RedirectURL["/*"];
    Send(soc,path,RedirectURL["/*"]);
  }
  else
  {
    std::string tmp=BAD_RESPONSE;
    const char* res=tmp.c_str();
    send(soc,res,strlen(res),0);
  }
}

void webs::Router::Send(int soc,std::string &path,std::string &url)
{
  if(file_exists(path))
  {
    std::string file,tmp;
    int idx=0;
    if(url=="/")
    {
      file=ENTRY_POINT;
      path+=ENTRY_POINT;
    }
    else
    {
      idx=path.find_last_of('/');
      file=path.substr(idx+1);
    }
    if(isImageFile(file))
    {
      std::vector<char> resbody=ReadImage(path);
      tmp=generate_response_headers(file);
      const char* res=tmp.c_str();
      send(soc,res,strlen(res),0);
      send(soc,resbody.data(),resbody.size(),0);
    }
    else
    {
      tmp=generate_response_headers(file);
      tmp+=ReadFile(path);
      const char* res=tmp.c_str();
      send(soc,res,strlen(res),0);
    }
  }
}