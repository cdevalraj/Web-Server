#ifndef Server_hpp
#define Server_hpp

#include<sys/socket.h>
#include<netinet/in.h>
#include<iostream>

namespace webs
{
    class WebServer
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