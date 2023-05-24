#include "../include/Server.hpp"

webs::WebServer::WebServer(int d,int t,int port,int s_add):Router()
{
    domain=d;
    type=t;
    address.sin_family=d;
    address.sin_port=htons(port);
    address.sin_addr.s_addr=htonl(s_add);
}

int webs::WebServer::initServer()
{
    int sfd=socket(domain,type,0),opt=1;
    test_connection(sfd,"Socket Connection Failed");
    test_connection(setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt)),"setting socket options Failed");

    test_connection(bind(sfd,(sockaddr *)&address,sizeof(address)),"Bind Failed");

    test_connection(listen(sfd,10),"Listen Failed");
    return sfd;
}

void webs::WebServer::test_connection(int to_test,const char * str)
{
    if(to_test<0)
    {
        perror(str);
        exit(EXIT_FAILURE);
    }
}