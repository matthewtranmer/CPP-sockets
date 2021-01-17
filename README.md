## INFO 
Sockets is an open-source C++ library that was designed to act like the python socket library.  
Sockets allows you to create multiple socket objects and communicate with them independently. 

## DISCLAMER 
The current version of this library should be used with extreme caution as the writer has made it to learn more about how C++ and sockets work. 
It has only been tested using the AF_INET family, the TCP protocol and on Ubuntu. 
I would highly recommend you check through the code before implementing it in your program. 
Any help would be appreciated to improve this library. 

## EXAMPLES OF USE 
This program will use the sockets library to make a simple TCP server using the AF_INET family. 
``` c++
#include "Socket.h" 
#include <iostream> 

int main(){ 
    //create the socket object 
    sockets::Socket server(AF_INET, SOCK_STREAM); 

    //you can miss this out as it is unnecessary. sets a socket option 
    //so the socket can reuse the address and port. 
    server.setsockopt(SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 1); 

    //bind it to an IP address and port 
    server.bind("127.0.0.1", 7000); 

    //listen for connections and make a backlog of up to 5 connections 
    server.listen(5); 

    //make block run forever 
    while (true){ 
        //create a new socket object to the client 
        sockets::Socket conn = server.accept(); 
        
        //send a message to the client 
        conn.send("You are now connected to the server!"); 

        //receive a message from the client and display it with a 1024 char buffer size
        std::cout << conn.recv(1024) << std::endl; 

        //close the connection 
        conn.close(); 

    } 

} 
```

This program will use the sockets library to make a simple TCP client using the AF_INET family.
``` c++
#include "Socket.h"
#include <iostream>

int main(){
    //create the socket object 
    sockets::Socket client(AF_INET, SOCK_STREAM);

    //connect to the servers IP address and port
    client.connect("127.0.0.1", 7000);

    //send a message to the server
    client.send("I am the client!");
    
    //receive a message from the server and display it with a 1024 char buffer size
    std::cout << client.recv(1024) << std::endl;
}
```













