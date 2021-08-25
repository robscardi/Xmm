#ifndef __GUARD_CONNECTION_HPP
#define __GUARD_CONNECTION_HPP



#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include "struct.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

namespace X11{


#define _ORDER 'l'
#define _PROT_MAJOR_VERSION 11
#define _PROT_MINOR_VERSION 0

#ifdef _SOCAT_DEBUG
        #define _SOCKET_FILE "/tmp/socat-listen"
#else
        #define _SOCKET_FILE "/tmp/.X11-unix/X0"
#endif
#define _AUTH_PROTOCOL "MIT-MAGIC-COOKIE-1\0\0"




class connection{
        public:
        connection();

        size_t send();
        size_t receive();

        private:
        int socket_fd;
        X11::connection_reply_header_t header;
        X11::connection_reply_success_body_t body;



};

}

#endif