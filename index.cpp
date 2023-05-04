#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>
#include<string.h>
#include "./include/Server.hpp"
#include "./include/Response.hpp"
#include<fstream>
#include<vector>
#define PORT 3000

using namespace std;

int sfd,new_soc;
string fname[]={"./dist/index.html","./dist/assets/index-86d1dd50.css","./dist/assets/index-bf49b193.js","./dist/assets/index-flash.ico"};

void shut(int );
string FileRead(int );
vector<char> read_image_file();

int main(int argc,char** argv)
{
    int port=(argc>=2)?stoi(argv[1]):PORT;
    webs::WebServer ws(AF_INET,SOCK_STREAM,port,INADDR_ANY);
    sfd=ws.initServer();
    cout<<"Server Started listening on port:"<<port<<endl;
    signal(SIGINT,shut);
    int addrlen=sizeof(ws.address);
    string s1=GOOD_RESPONSE,s2=GOOD_RESPONSE,s3=GOOD_RESPONSE,s4=GOOD_RESPONSE;
    s1+="Content-Type: text/html\n\n"+FileRead(1);
    s2+="Content-Type: text/css\n\n"+FileRead(2);
    s3+="Content-Type: application/javascript\n\n"+FileRead(3);
    s4+="Content-Type: image/x-icon\n\n";
    vector<char> img=read_image_file();
    const char* res1=s1.c_str();
    const char* res2=s2.c_str();
    const char* res3=s3.c_str();
    const char* res4=s4.c_str();
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
        if(URL=="/")
        {
            send(new_soc,res1,strlen(res1),0);
            // write(new_soc,res,strlen(res));
        }
        else if(URL=="/assets/index-86d1dd50.css")
        {
            send(new_soc,res2,strlen(res2),0);
        }
        else if(URL=="/assets/index-bf49b193.js")
        {
            send(new_soc,res3,strlen(res3),0);
        }
        else if(URL=="/assets/index-flash.ico")
        {
            send(new_soc,res4,strlen(res4),0);
            send(new_soc,img.data(),img.size(),0);
        }
        // else
        // {}
        close(new_soc);
    }
    return 0;
}

string FileRead(int fn)
{
    if(fn<=0 || fn>3)
    {
        cout<<"No such File exists"<<endl;
        return "";
    }
    ifstream f;
    string str,tmp;
    f.open(fname[fn-1],ios::in);
    while(getline(f,tmp))
        {str+=tmp;}
    f.close();
    return str;
}

vector<char> read_image_file()
{
    ifstream file(fname[3],ios::binary | ios::ate);
    if(!file)
    {
        throw runtime_error("Failed to open file: "+fname[3]);
    }
    long file_size=file.tellg();
    file.seekg(0,ios::beg);
    vector<char> buffer(file_size);
    if(!file.read(buffer.data(),file_size))
    {
        throw std::runtime_error("Failed to read file: "+fname[3]);
    }
    return buffer;
}

void shut(int s)
{
    cout<<"\nShutting Down\n\n";
    close(new_soc);
    close(sfd);
    exit(EXIT_FAILURE);
}