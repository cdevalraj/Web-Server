# WEB-SERVER

This is Web Server which can listen to the HTTP requests on the specified host and port no. and can also send HTTP responses on that same end-point.

## TO RUN/START The Server
To Run this code the code needs to be compiled and executed. So, by using the following commands you can start the server.
```
$ g++ src/FileHandling.cpp src/Response.cpp src/Server.cpp index.cpp -o a.exe
$ ./a.exe [port no.]
```

## Note
* Place your Requried html files in `./app/` app directory (in the root this Repo) in the same directory as this file
* Also js, css, images, and others files inside assets folder i.e. `./app/assets`\
(For now this is not important, in future it will be)
* This code only works in Linux systems.
* This is still `UNDER DEVELOPMENT`

### Thank You
Also if there are any modifications/optimizations, feel free to notify me or Raise a pull request.