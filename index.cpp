#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>
#include<string.h>
#include "./include/Server.hpp"
#include "./include/Response.hpp"
#include<fstream>
#define PORT 3000

using namespace std;

int sfd,new_soc;
ifstream f1("./dist/index.html"),f2("./dist/assets/index-86d1dd50.css"),f3("./dist/assets/index-bf49b193.js");

void shut(int );
string FileRead(string );

int main(int argc,char** argv)
{
    int port=(argc>=2)?stoi(argv[1]):PORT;
    webs::WebServer ws(AF_INET,SOCK_STREAM,port,INADDR_ANY);
    sfd=ws.initServer();
    cout<<"Server Started listening on port:"<<port<<endl;
    signal(SIGINT,shut);
    int addrlen=sizeof(ws.address);
    string s1=GOOD_RESPONSE,s2=GOOD_RESPONSE,s3=GOOD_RESPONSE;
    s1+=FileRead("f1");
    s2+=FileRead("f2");
    s3+=FileRead("f3");

    const char* res1=s1.c_str();
    const char* res2=s2.c_str();
    const char* res3=s3.c_str();
    while(true)
    {
        new_soc=accept(sfd,(sockaddr *)&ws.address,(socklen_t*)&addrlen);
        ws.test_connection(new_soc,"Accept Failed");
        char buffer[30000]={0};
        read(new_soc,buffer,30000);
        char* token=strtok(buffer," ");
        // string Rest;
        // Rest.assign(token,token+strlen(token));
        token=strtok(NULL," ");
        string URL;
        URL.assign(token,token+strlen(token));
        if(URL=="/")
        {
            send(new_soc,res1,strlen(res1),0);
            // write(new_soc,res,strlen(res));
        }
        else if(URL=="/assets/index-bf49b193.js")
        {
            send(new_soc,res2,strlen(res2),0);
        }
        else if(URL=="/assets/index-86d1dd50.css")
        {
            send(new_soc,res3,strlen(res3),0);
        }
        // else
        // {}
        close(new_soc);
    }
    return 0;
}

string FileRead(string f)
{
    string str,tmp;
    if(f=="f1")
    {
        while(getline(f1,tmp))
        {str+=tmp;}
    }
    else if(f=="f2")
    {
        while(getline(f2,tmp))
        {str+=tmp;}
    }
    else
    {
        while(getline(f3,tmp))
        {str+=tmp;}
    }
    return str;
}

void shut(int s)
{
    cout<<"\nShuting Down\n\n";
    f1.close();
    f2.close();
    f3.close();
    close(new_soc);
    close(sfd);
    exit(EXIT_FAILURE);
}