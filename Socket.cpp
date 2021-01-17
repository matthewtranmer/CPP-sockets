#include "Socket.h"
#include <unistd.h>

sockets::Socket::Socket(int family, int type, int protocol, int socket){
    this->family = family;
    this->type = type;
    this->protocol = protocol;

    if (socket == -404){
        this->socket = ::socket(this->family, this->type, this->protocol);
    }
    else{
        this->socket = socket;
    }
}

//server modules
void sockets::Socket::bind(std::string ip, int port){
    address.sin_family = family;
    address.sin_port = htons(port);

    ::inet_pton(AF_INET, ip.c_str(), &address.sin_addr);
    ::bind(socket, (struct sockaddr *)&address, sizeof(address));
}


void sockets::Socket::setsockopt(int level, int optname, int value){
    const void* value_ptr = &value;
    ::setsockopt(socket, level, optname, value_ptr, sizeof(value_ptr));
}

void sockets::Socket::listen(int backlog){
    ::listen(socket, backlog);
}

sockets::Socket sockets::Socket::accept(){
    int connection = ::accept(socket, (struct sockaddr *)&address, (socklen_t*)&addresslen);
    return Socket(family, type, protocol, connection);

}

//client modules
void sockets::Socket::connect(std::string ip, int port){
    address.sin_family = family;
    address.sin_port = htons(port);

    ::inet_pton(AF_INET, ip.c_str(), &address.sin_addr);
    ::connect(socket, (struct sockaddr *)&address, sizeof(address));
}

//misc modules
void sockets::Socket::close(){
    ::close(socket);
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
