#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <string>

namespace sockets{
    class Socket{
        private:
            int socket;
            int family;
            int type;
            int protocol;
            int port;
            int addresslen;
            int return_val;

            struct ::sockaddr_in address;

        public:
            Socket(int, int, int=0, int=-404);

            //server modules
            void bind(std::string, int);
            void setsockopt(int, int, int);
            void listen(int);
            Socket accept();

            //client modules
            void connect(std::string, int);

            //misc modules
            void close();
            void send(std::string, int=0);
            std::string recv(int);
    };
};
#endif // SOCKET_H
