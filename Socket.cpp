#include "Socket.h"
#include <unistd.h>
#include <iostream>

sockets::Socket::Socket(int family, int type, int protocol, int socket){
    this->family = family;
    this->type = type;
    this->protocol = protocol;

    if (socket == -404){
        if((this->socket = ::socket(this->family, this->type, this->protocol)) < 0){
            std::cout << "Error - Socket creation failed" << std::endl;
            throw 1;
        }
    }
    else{
        this->socket = socket;
    }
}

//server modules
void sockets::Socket::bind(std::string ip, int port){
    address.sin_family = family;
    address.sin_port = htons(port);

    return_val = ::inet_pton(AF_INET, ip.c_str(), &address.sin_addr);
    if (return_val <= 0){
        std::cout << "Error - Invalid address" << std::endl;
        throw 2;
    }

    return_val = ::bind(socket, (struct sockaddr *)&address, sizeof(address));
    if(return_val < 0){
        std::cout << "Error - Bind failed" << std::endl;
        throw 3;
    }
}


void sockets::Socket::setsockopt(int level, int optname, int value){
    const void* value_ptr = &value;

    return_val = ::setsockopt(socket, level, optname, value_ptr, sizeof(value_ptr));
    if(return_val < 0){
        std::cout << "Error - Setsockopt failure" << std::endl;
        throw 4;
    }
}

void sockets::Socket::listen(int backlog){
    if(::listen(socket, backlog) < 0){
        std::cout << "Error - Couldn't listen" << std::endl;
        throw 5;
    }
}

sockets::Socket sockets::Socket::accept(){
    int connection;
    if((connection = ::accept(socket, (struct sockaddr *)&address, (socklen_t*)&addresslen)) < 0){
        std::cout << "Error - Couldn't accept connection" << std::endl;
        throw 6;
    }
    return Socket(family, type, protocol, connection);

}

//client modules
void sockets::Socket::connect(std::string ip, int port){
    address.sin_family = family;
    address.sin_port = htons(port);

    return_val = ::inet_pton(AF_INET, ip.c_str(), &address.sin_addr);
    if (return_val <= 0){
        std::cout << "Error - Invalid address" << std::endl;
        throw 7;
    }

    return_val = ::connect(socket, (struct sockaddr *)&address, sizeof(address));
    if (return_val < 0){
        std::cout << "Error - Connection failed" << std::endl;
        throw 8;
    }
}

//misc modules
void sockets::Socket::close(){
    if(::close(socket) < 0){
        std::cout << "Error - Connection failed to close" << std::endl;
        throw 9;
    }
}

void sockets::Socket::send(std::string data, int flags){
    ::send(socket, data.c_str(), data.length(), flags);
}

std::string sockets::Socket::recv(int buffer_size){
    char buffer[buffer_size] = {};
    read(socket, buffer, buffer_size);

    std::string data_recvd = buffer;
    return data_recvd;
}
