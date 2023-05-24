# WEB-SERVER

This is a Web Server which is built using socket programming in c++ under the hood, which can listen to the requests on the specified host and port no. and can also send HTTP responses on that same end-point. Unlike other servers which can handle multiple projects/applications, unfortunately this web server is not capable(in future this will be handlded).

## TO RUN/START The Server
To Run this code the code needs to be compiled and executed. So, by using the following commands you can start the server.
```
g++ src/File_Handler.cpp src/Response_Handler.cpp src/Request_Handler.cpp src/Router.cpp src/Server.cpp index.cpp -o a.exe
```
```
./a.exe [port no.]
```

## Note
* Place your Requried html files in `./app/` app directory (in the root this Repo) in the same directory as this file
* Also js, css, images, and others files inside assets folder i.e. `./app/assets`
* This code only works in Linux systems with gnu17++ compiler config.
* For Any Redirects in your application/project you need to specify them in the `rconfig.json` in the root of the app directory. \
The JSON file should be in the following format
```
{
    "from":"to",
    ...
}
```
* This is still `UNDER DEVELOPMENT`

### Thank You
Also if there are any modifications/optimizations, feel free to notify me or Raise a pull request.