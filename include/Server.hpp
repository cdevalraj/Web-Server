#ifndef Server_hpp
#define Server_hpp

#include<netinet/in.h>
#include "Router.hpp"

namespace webs
{
    class WebServer: public Router
    {
        public:
            int domain,type;
            sockaddr_in address;
            WebServer(int domain,int type,int port,int s_add);
            int initServer();
            void test_connection(int ,const char * );
    };
}

#endif