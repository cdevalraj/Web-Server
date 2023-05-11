#ifndef Routing_hpp
#define Routing_hpp

#define ENTRY_POINT "index.html"
#define ROUTE_CONFIG "rconfig.json"

#include "FileHandling.hpp"

namespace webs
{
    class Routing : public FileHandling
    {
        public:
            std::unordered_map<std::string,std::string> RedirectURL;
            std::unordered_map<std::string,std::string> Route_files;
            std::unordered_map<std::string,std::vector<char>> Route_images;
            Routing();
    };
}


#endif