#ifndef Server_hpp
#define Server_hpp

#include<sys/socket.h>
#include<netinet/in.h>
#include<iostream>

namespace webs
{
    int initServer(int domain,int type,int port,int s_add);
    void test_connection(int ,const char * );
}

#endif