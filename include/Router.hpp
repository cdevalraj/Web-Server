#ifndef Router_hpp
#define Router_hpp

#define ENTRY_POINT "index.html"
#define APP "./app"
#define REROUTE_CONFIG "./app/rconfig.json"

#include "File_Handler.hpp"
#include "Request_Handler.hpp"
#include "Response_Handler.hpp"
#include <sys/stat.h>

namespace webs
{
    class Router : public File_Handler, public Request_Handler , public Response_Handler
    {
        public:
            std::unordered_map<std::string,std::string> RedirectURL;
            // std::unordered_map<std::string,std::string> Route_files;
            // std::unordered_map<std::string,std::vector<char>> Route_images;
            Router();
            void Route(int soc);
            void Send(int soc,std::string &path,std::string &url);
    };
}


#endif