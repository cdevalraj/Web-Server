#include "../include/Request_Handler.hpp"

webs::Request_Handler::Request_Handler()
{

}

std::unordered_map<std::string,std::string> webs::Request_Handler::handleReq(int soc)
{
    std::unordered_map<std::string,std::string> req;
    char buffer[30000]={0};
    int size=recv(soc,buffer,30000,0);
    
    try
    {
        //Parsing the request
        std::string firstline;
        int i=0,tmp=0;
        std::string str="";
        std::string keys[]={"method","path","type"};
        for(;i<strlen(buffer);i++)
        {
            if(buffer[i]=='\n')
                break;
            else if(buffer[i]!=' ')
                str+=buffer[i];
            else
            {
                req[keys[tmp++]]=str;
                str="";
            }
        }
        req[keys[tmp]]=str;
        i++;
        for(;buffer[i]!='\0';i++)
        {
            if(buffer[i]=='\n')
            {
                if(str.find(':')!=-1)
                {
                    int j=0;
                    std::string key,value;
                    for(;j<str.length();j++)
                    {
                        if(str[j]==':')
                            break;
                        key+=str[j];
                    }
                    // std::cout<<key<<" "<<str.length()<<" "<<j<<std::endl;
                    value=str.substr(j+1);
                    req[key]=value;
                }
                str="";
            }
            else
                str+=buffer[i];
        }
        if(str.find(":")!=std::string::npos)
        {
            i=0;
            std::string key,value;
            for(;i<str.length();i++)
            {
                if(str[i]==':')
                    break;
                key+=str[i];
            }
            value=str.substr(i+1);
            req[key]=value;
        }
    }
    catch(...)
    {
        std::cout<<"Invalid Request\n"<<std::endl;
    }
    return req;
}
// if(str.find("GET")!=std::string::npos || str.find("POST")!=std::string::npos || str.find("PUT")!=std::string::npos || str.find("DELETE")!=std::string::npos || str.find("HEAD")!=std::string::npos || str.find("CONNECT")!=std::string::npos || str.find("OPTIONS")!=std::string::npos || str.find("TRACE")!=std::string::npos)