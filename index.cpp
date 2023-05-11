#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>
#include<string.h>
#include "./include/Server.hpp"
#include <vector>
#include <filesystem>
#define PORT 3000

namespace fs = std::filesystem;
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
        char buffer[30000]={0};
        read(new_soc,buffer,30000);
        char* token=strtok(buffer," ");
        string REST_PROTO;
        REST_PROTO.assign(token,token+strlen(token));
        token=strtok(NULL," ");
        string URL;
        URL.assign(token,token+strlen(token));
        fs::path path_name = URL;
        string file=path_name.filename();
        string tmp;
        if(ws.Route_files.find(URL)!=ws.Route_files.end())
        {
            tmp=ws.generate_response(file);
            tmp+=ws.Route_files[URL];
            const char* res=tmp.c_str();
            send(new_soc,res,strlen(res),0);
        }
        else if(ws.Route_images.find(URL)!=ws.Route_images.end())
        {
            tmp=ws.generate_response(file);
            vector<char> img=ws.Route_images[URL];
            tmp+=ws.Route_files[URL];
            const char* res=tmp.c_str();
            send(new_soc,res,strlen(res),0);
            send(new_soc,img.data(),img.size(),0);
        }
        else if(ws.RedirectURL.find(URL)!=ws.RedirectURL.end())
        {
            path_name=ws.RedirectURL[URL];
            file=path_name.filename();
            tmp=ws.generate_response(file);
            tmp+=ws.Route_files[URL];
            const char* res=tmp.c_str();
            send(new_soc,res,strlen(res),0);
        }
        else if(ws.RedirectURL.find("/*")!=ws.RedirectURL.end())
        {
            tmp=HTML_RESPONSE;
            tmp+=ws.Route_files["/"];
            const char* res=tmp.c_str();
            send(new_soc,res,strlen(res),0);
        }
        else
        {
            tmp=BAD_RESPONSE;
            const char* res=tmp.c_str();
            send(new_soc,res,strlen(res),0);
        }
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