#ifndef Request_Handler_hpp
#define Request_Handler_hpp

#include "Headers.hpp"

namespace webs
{
    class Request_Handler
    {
        public:
            Request_Handler();
            std::unordered_map<std::string,std::string> handleReq(int soc);
    };
}

#endif