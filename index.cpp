#include "./include/Server.hpp"
#include<signal.h>
#define PORT 3000

using namespace std;

int sfd,new_soc;

void shut(int );

int main(int argc,char** argv)
{
    int port=(argc>=2)?stoi(argv[1]):PORT;
    webs::WebServer ws(AF_INET,SOCK_STREAM,port,INADDR_ANY);
    sfd=ws.initServer();
    int addrlen=sizeof(ws.address);
    cout<<"Server Started listening on port:"<<port<<endl;

    signal(SIGINT,shut);
    while(true)
    {
        new_soc=accept(sfd,(sockaddr *)&ws.address,(socklen_t*)&addrlen);
        ws.test_connection(new_soc,"Accept Failed");
        ws.Route(new_soc);
        close(new_soc);
    }
    return 0;
}

void shut(int s)
{
    cout<<"\nShutting Down\n\n";
    close(new_soc);
    close(sfd);
    exit(EXIT_FAILURE);
}