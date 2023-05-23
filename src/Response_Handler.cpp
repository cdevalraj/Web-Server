#include "../include/Response_handler.hpp"

webs::Response_Handler::Response_Handler()
{
    Respnoses["html"]=HTML_RESPONSE;
    Respnoses["js"]=JS_FILE_RESPONSE;
    Respnoses["css"]=CSS_FILE_RESPONSE;
    Respnoses["jpg"]=JPGE_RESPONSE;
    Respnoses["svg"]=SVG_RESPONSE;
    Respnoses["gif"]=GIF_RESPONSE;
}

std::string webs::Response_Handler::generate_response(std::string file)
{
    if(file=="")
        return HTML_RESPONSE;
    int start=file.find_last_of('.');
    if(start!=std::string::npos)
    {
        std::string extension=file.substr(start+1);
        return Respnoses[extension];
    }
    return GOOD_RESPONSE;
}