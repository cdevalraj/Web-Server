#include "../headers/Server.hpp"

int webs::initServer(int domain,int type,int port,int s_add)
{
    int sfd=socket(domain,type,0);
    test_connection(sfd,"Socket Connection Failed");

    sockaddr_in address;
    address.sin_family=domain;
    address.sin_port=htons(port);
    address.sin_addr.s_addr=s_add;

    test_connection(bind(sfd,(sockaddr *)&address,sizeof(address)),"Bind Failed");

    test_connection(listen(sfd,10),"Listen Failed");
    return sfd;
}

void webs::test_connection(int to_test,const char * str)
{
    if(to_test<0)
    {
        perror(str);
        exit(EXIT_FAILURE);
    }
}