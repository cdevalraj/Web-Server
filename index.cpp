#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>
#include<string.h>
#include "./headers/Server.hpp"
#define PORT 3000

using namespace std;

int sfd,new_soc;

void shut(int );

int main(int argc,char** argv)
{
    int port=(argc>=2)?stoi(argv[1]):PORT;
    sfd=webs::initServer(AF_INET,SOCK_STREAM,port,INADDR_ANY);
    signal(SIGINT,shut);
    while(true)
    {
        cout<<"Waiting\n";
        new_soc=accept(sfd,NULL,NULL);
        webs::test_connection(new_soc,"Accept Failed");
        char buffer[30000]={0};
        read(new_soc,buffer,30000);
        cout<<buffer;
        cout<<"Done\n\n";
        close(new_soc);
    }
    return 0;
}
void shut(int s)
{
    cout<<"\nShuting Down\n\n";
    close(new_soc);
    close(sfd);
    // shutdown(sfd,SHUT_RDWR);
    exit(EXIT_FAILURE);
}