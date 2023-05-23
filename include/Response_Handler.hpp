#ifndef Response_Handler_hpp
#define Response_Handler_hpp

#define GOOD_RESPONSE  "HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nServer: MyServer\r\n"
#define BAD_RESPONSE  "HTTP/1.1 404 OK\r\nConnection: keep-alive\r\nServer: MyServer\r\n\n"

#define HTML_RESPONSE  GOOD_RESPONSE"Content-Type: text/html\r\n\n"

#define JS_FILE_RESPONSE  GOOD_RESPONSE"Content-Type: application/javascript\r\n\n"

#define CSS_FILE_RESPONSE  GOOD_RESPONSE"Content-Type: text/css\r\n\n"

#define JPGE_RESPONSE  GOOD_RESPONSE"Content-Type: image/jpeg\r\n\n"
#define PNG_RESPONSE  GOOD_RESPONSE"Content-Type: image/png\r\n\n"
#define APNG_RESPONSE  GOOD_RESPONSE"Content-Type: image/apng\r\n\n"
#define GIF_RESPONSE  GOOD_RESPONSE"Content-Type: image/gif\r\n\n"
#define AVIF_RESPONSE  GOOD_RESPONSE"Content-Type: image/avif\r\n\n"
#define SVG_RESPONSE  GOOD_RESPONSE"Content-Type: image/svg+xml\r\n\n"
#define WEBP_RESPONSE  GOOD_RESPONSE"Content-Type: image/webp\r\n\n"

#include "Headers.hpp"


namespace webs
{
    class Response_Handler
    {
        std::unordered_map<std::string,std::string> Respnoses;
        public:
            Response_Handler();
            std::string generate_response(std::string file);
    };
}


#endif